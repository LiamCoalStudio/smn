#include "module.h"
#include "use.h"
#include <dlfcn.h>
#include <unordered_map>
#include <filesystem>

using namespace std;
using namespace filesystem;

unordered_map<str, void*> handles;
extern std::unordered_map<str, std::list<LanguageElement*>> usable;

/**
 * Loads a module, allowing you to `use module` on it.
 * @param name Module to load
 */
void load(const str& name)
{
    // Check if already loaded. Will be used later.
    if (handles.contains(name)) return;

    // Get the path to the module.
    //
    // If in testing mode, use the build path for modules. Otherwise,
    // use the normal paths of /usr/share/simon/modules and ./
    str s = "./lib" + name + ".so";
    if(!exists(path(s))) s = "/usr/share/simon/modules/lib" + name + ".so";
    if(!exists(path(s)))
    {
        print_error("cannot find module " << name);
        exit(1);
    }

    // Open and ensure there are no errors.
    handles[name] = dlopen(s.c_str(), RTLD_LAZY);
    char *err = dlerror();
    if (err != nullptr)
    {
        // If errored, cannot continue as Simon doesn't know
        // if you used that module or not.
        print_error("while loading module " << name << ": " << err);
        exit(1);
    }
}

/**
 * Special use function for using from a module.
 * @param module Module to use from. (must be loaded first)
 * @param name Name of the thing to use.
 */
void use(const str& module, const str& name)
{
    void* func = dlsym(handles[module], ("module_use_" + name).c_str());
    char *err = dlerror();
    if (err != nullptr)
    {
        print_error("while using " << name << " from module " << module << ": " << err);
        exit(1);
    }
    ((void(*)(std::unordered_map<str, std::list<LanguageElement*>>*))func)(&usable);
    use(name);
}

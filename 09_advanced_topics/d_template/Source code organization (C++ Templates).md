# Source code organization (C++ Templates)

> https://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp#:~:text=The%20common%20procedure%20in%20C%2B%2B%20is%20to%20put,classes%2C%20some%20compilation%20and%20linking%20problems%20will%20arise.

> https://docs.microsoft.com/en-us/cpp/cpp/source-code-organization-cpp-templates?view=msvc-170

When defining a class template, you must organize the source code in such a way that the member definitions are visible to the compiler when it needs them. You have the choice of using the inclusion model or the explicit instantiation model. In the inclusion model, you include the member definitions in every file that uses a template. This approach is simplest and provides maximum flexibility in terms of what concrete types can be used with your template. Its disadvantage is that it can increase compilation times. The impact can be significant if a project and/or the included files themselves are large. With the explicit instantiation approach, the template itself instantiates concrete classes or class members for specific types. This approach can speed up compilation times, but it limits usage to only those classes that the template implementer has enabled ahead of time. In general, we recommend that you use the inclusion model unless the compilation times become a problem.

# template specialization

> https://docs.microsoft.com/en-us/cpp/cpp/explicit-specialization-of-function-templates?view=msvc-170

> https://docs.microsoft.com/en-us/cpp/cpp/template-specialization-cpp?view=msvc-170

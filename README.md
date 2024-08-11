# events
A simple, small and fast event processing lib. 

## Build example
```
cmake --preset clang-debug
cd build/clang-debug
cmake --build .
```

## Runing tests
```ctest```
(From inside build folder)

## Using in a cmake project
```
include(FetchContent)

FetchContent_Declare(
  events 
  GIT_REPOSITORY https://www.github.com/mttjcksn/events
  GIT_TAG  main
)

FetchContent_MakeAvailable(events)
```

And link with events-lib or reference source files with:

```"${events_SOURCE_DIR}/src"```
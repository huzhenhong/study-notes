# __thread 和 thread_local

### differnce

- __thread is supported on GNU, clang and more. It was available before thread_local.

- they are not equivalent and both are supported. the difference is that
  - thread_local uses lazy initialization to initialize the variable in only threads that access it.（延迟初始化，access 应该是指首次访问）
  - __thread does not initialize at all and you must manually initialize it per thread.（需要手动初始化）

- thread_local thus has an overhead per access and __thread does NOT.

- Apple’s compilers disable thread_local and not thread because of this inefficiency,

- thread is available with GNU tools

###  The __thread specifier may be applied to 

- any global
- file-scoped static
- function-scoped static
- static data member of a class

It may not be applied to block-scoped automatic or non-static data member.

### thread_local

既可以用于全局变量，也可以用于局部变量


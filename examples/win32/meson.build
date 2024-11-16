project('win32_example', 'cpp',
    version : '0.0.1',
    default_options : [
        'cpp_std=c++14',
        'b_sanitize=none',
        'b_lto=false',
        'b_pch=false',
        'buildtype=debug'
    ]
)

# Get compiler object
cpp = meson.get_compiler('cpp')

# Add Windows and Unicode specific definitions
windows_args = [
    '-DUNICODE',
    '-D_UNICODE',
    '-DWIN32',
    '-D_WINDOWS',
    '-DCOBJMACROS',
    '-D_DEBUG',
    '-D_CRT_SECURE_NO_WARNINGS'
]

# Add linker arguments for static linking
link_args = [
    '-static',
    '-static-libgcc',
    '-static-libstdc++',
    '--enable-stdcall-fixup',
    '-Wl,-Bstatic',
]

# Source files
src_files = files(
    'main.cpp'
)

src_dir = meson.current_source_dir()

# Determine the architecture and set the paths accordingly
if host_machine.cpu_family() == 'x86_64'

    # Path to MingW
    message('Selecting MingW x86_64 architecture')
    mingw_path = 'C:/msys64/mingw64'

elif host_machine.cpu_family() == 'x86'

    # Path to MingW
    message('Selecting MingW x86 architecture')
    mingw_path = 'C:/msys64/mingw32'

endif

# Include directories
inc_dirs = [
    include_directories('../../include'),
    include_directories('../../distorm3/include'),
    include_directories(mingw_path + '/include')
]

# Library paths
lib_path = mingw_path + '/lib'

# Define dependencies
distormx_dep = cpp.find_library('distormx', static : true, dirs : [mingw_path])

# Build the EXE
executable('win32_example',
    src_files,
    include_directories : inc_dirs,
    dependencies : [
        distormx_dep
    ],
    cpp_args : windows_args,
    link_args : link_args,
    name_prefix : ''
)
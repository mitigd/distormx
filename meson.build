project('distormx', 'c',
    version : '3.5.2',
    default_options : [
        'c_std=c11',
        'buildtype=release'
    ]
)

# Get compiler object
cpp = meson.get_compiler('c')

# Source files
src_files = files(
    'distorm3/src/decoder.c',
    'distorm3/src/distorm.c',
    'distorm3/src/instructions.c',
    'distorm3/src/insts.c',
    'distorm3/src/mnemonics.c',
    'distorm3/src/operands.c',
    'distorm3/src/prefix.c',
    'distorm3/src/textdefs.c',
    'src/distormx.c',
    'src/OS.c'
)

# Determine the architecture and set the paths accordingly
if host_machine.cpu_family() == 'x86_64'
    # Path to MingW
    message('Selecting MingW x86_64 architecture')
    mingw_path = 'C:/msys64/mingw64'
    install_dir = 'C:/msys64/mingw64/lib'
elif host_machine.cpu_family() == 'x86'
    # Path to MingW
    message('Selecting MingW x86 architecture')
    mingw_path = 'C:/msys64/mingw32'
    install_dir = 'C:/msys64/mingw32/lib'
endif

# Include directories
inc_dirs = [
    include_directories('src'),
    include_directories('distorm3/include'),
    include_directories('distorm3/src'),
    include_directories('include'),
    include_directories(mingw_path + '/include')
]

# Library paths
lib_path = mingw_path + '/lib'
kernel32_dep = cpp.find_library('kernel32')

# Build the Static Library
static_library('distormx',
    src_files,
    include_directories : inc_dirs,
    dependencies : [
        kernel32_dep
    ],
    name_prefix : '',
    install : true,
    install_dir : install_dir
)
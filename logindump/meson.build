project(
  'logindump',
  'c',
  meson_version : '>= 0.61.0',
  default_options : [
                  'prefix=/usr',
                  'sysconfdir=/etc',
                  'localstatedir=/var',
                  'buildtype=debugoptimized',
  		  'default_library=shared',
		  'b_pie=true',
                  'b_lto=true',
                  'c_std=gnu17',
		  'warning_level=2'],
  license : ['GPL-2.0-or-later', 'LGPL-2.1-or-later'],
  version : '0.1.0',
)

conf = configuration_data()
conf.set_quoted('VERSION', meson.project_version())
conf.set_quoted('PACKAGE', meson.project_name())

cc = meson.get_compiler('c')
pkg = import('pkgconfig')

add_project_arguments(['-D_GNU_SOURCE=1',
		       '-DXTSTRINGDEFINES',
		       '-D_FORTIFY_SOURCE=2',
                       '-D_FILE_OFFSET_BITS=64',
                       '-D_TIME_BITS=64'], language : 'c')

possible_cc_flags = [
		  '-fstack-protector-strong',
		  '-funwind-tables',
		  '-fasynchronous-unwind-tables',
		  '-fstack-clash-protection',
		  '-Wbad-function-cast',
                  '-Werror',
		  '-Wcast-align',
                  '-Wformat-security',
		  '-Wmissing-declarations',
		  '-Wmissing-prototypes',
		  '-Wnested-externs',
		  '-Wshadow',
		  '-Wstrict-prototypes',
		  '-Wundef',
                  '-Wuninitialized',
		  ]
add_project_arguments(cc.get_supported_arguments(possible_cc_flags), language : 'c')

libsystemd = dependency('libsystemd', version: '>= 254', required : true)
libwtmpdb = dependency('libwtmpdb',  required : true)

logindump_c = ['src/main.c', 'src/logind.c', 'src/utmpwtmp.c', 
               'src/wtmpdb.c', 'src/strv.c']

executable('logindump',
           logindump_c,
           dependencies : [libsystemd,libwtmpdb],
           install : true)

# Unit tests
#subdir('tests')

# Manual pages
#subdir('man')

config_h = configure_file(
  output : 'config.h',
  configuration : conf)

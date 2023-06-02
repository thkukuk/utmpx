project(
  'utmpld',
  'c',
  meson_version : '>= 0.49.0',
  default_options : ['buildtype=debugoptimized',
  		  'default_library=shared',
		  'b_pie=true',
		  'warning_level=3',],
  license : 'LGPL-2.1+',
  version : '0.0.1',
)

cc = meson.get_compiler('c')
pkg = import('pkgconfig')
inc = include_directories('include')

add_project_arguments(['-D_GNU_SOURCE=1',
		       '-DXTSTRINGDEFINES',
		       '-D_FORTIFY_SOURCE=2'], language : 'c')

possible_cc_flags = [
                  '-Dwerror=true',
                  '-flto=auto',
                  '-ffat-lto-objects',
		  '-fstack-protector-strong',
		  '-funwind-tables',
		  '-fasynchronous-unwind-tables',
		  '-fstack-clash-protection',
		  '-Werror=return-type',
		  '-Wbad-function-cast',
		  '-Wcast-align',
		  '-Wcast-qual',
		  '-Winline',
		  '-Wmissing-declarations',
		  '-Wmissing-prototypes',
		  '-Wnested-externs',
		  '-Wshadow',
		  '-Wstrict-prototypes',
		  '-Wundef',
		  ]
add_project_arguments(cc.get_supported_arguments(possible_cc_flags), language : 'c')

libsystemd = cc.find_library('systemd')

libutmpld_src = files(
  'lib/get_session_id.c',
  'lib/set_tty.c',
)

mapfile = 'lib/libutmpld.map'
version_flag = '-Wl,--version-script,@0@/@1@'.format(meson.current_source_dir(), mapfile)

libutmpld = library(
  'utmpld',
  libutmpld_src,
  include_directories : inc,
  install : true,
  link_args : version_flag,
  link_depends : mapfile,
  dependencies : [libsystemd],
  version : meson.project_version(),
  soversion : '0',
)

#utmplddump_src = ['example/utmplddump.c']
utmpld_set_tty_src = ['example/utmpld_set_tty.c']

install_headers('include/utmpld.h')

pkg.generate(
  libutmpld,
  name : 'libutmpld',
  description : 'Library using systemd-logind as utmp replacement',
  version : meson.project_version(),
)

libutmpld_dep = declare_dependency(
  link_with : libutmpld,
  include_directories : inc,
)

# executable('utmplddump', utmplddump_src, dependencies : libutmpld_dep)
executable('utmpld_set_tty', utmpld_set_tty_src, dependencies : libutmpld_dep)

# Unit tests
subdir('tests')

# documentation
#subdir('doc')

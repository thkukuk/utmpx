# This file builds and runs the unit tests

tst_set_tty = executable ('tst-set_tty', 'tst-set_tty.c',
                        include_directories : inc,
                        link_with : libutmpld,
                        dependencies : [libsystemd])
test('tst-set_tty', tst_set_tty)

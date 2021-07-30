from behave import given, when, then
import pexpect

fix_executable = '../cmake-build-debug/bin/fix'


@given(u'nothing')
def nothing(context):
    pass


@when(u'we run Fix')
def start_fix(context):
    context.fix = pexpect.spawn(fix_executable)


@then(u'it prints "{expected_output}" and terminates')
def check_output(context, expected_output):
    fix = context.fix
    fix.expect_exact(expected_output)
    assert (fix.wait() == 0)

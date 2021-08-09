from behave import given, when, then
import fix_cli

@given(u'an empty issue repository')
def empty_repository(context):
    pass

@when(u'we list all issues')
def list_issues(context):
    fix_cli.start_fix(context, "list")

@when(u'we create an issue titled "{title}" with description')
def create_issue(context, title):
    description=context.text or ""
    fix_cli.start_fix(context, f'create --title "{title}" --descr "{description}"')
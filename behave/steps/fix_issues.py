from behave import given, when, then
import fix_cli


@given(u'an empty issue repository')
def empty_repository(context):
    pass


@when(u'we list all issues')
def list_issues(context):
    fix_cli.start_fix(context, "list")


def _create_issue(context, title, description):
    fix_cli.start_fix(context, f'create --title "{title}" --descr "{description}"')


@when(u'we create an issue titled "{title}" with description')
def create_issue(context, title):
    description = context.text or ""
    _create_issue(context, title, description)


@when(u'we create an issue titled "{title}"')
def create_issue_random_description(context, title):
    description = "Dorem Fixum dolor sit amet..."
    _create_issue(context, title, description)


@then(u'it prints a list of issues')
def check_issue_list(context):
    # first: column headings, separated by non-word characters,
    # then: entries for each column, again separated by non-word characters
    fix_cli.check_output_regex(context, r'ID\W+STATUS\W+TITLE')
    for row in context.table:
        fix_cli.check_output(context, fr'{row["issue ID prefix"]}-[hash]\W+{row["status"]}\W+"{row["title"]}"')


@then(u'it prints a list of {count:d} issues')
def check_issue_list_count(context, count):
    check_issue_list(context)
    fix_cli.check_output(f"total: {count} issues")

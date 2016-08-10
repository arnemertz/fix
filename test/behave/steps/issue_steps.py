from behave import *
from pathlib import Path
import requests


@given('an empty Fix repository')
def step_impl(context):
    pass


@when('we create issues')
def step_impl(context):
    table = context.table
    for row in table:
        issue_data = {}
        for key in table.headings:
            issue_data[key] = row[key]
        issue = {'data': issue_data}
        r = requests.post('http://localhost:8080/issue/new', json=issue)
        assert r.status_code == 200


@then('an issue file "{file_name}" exists in the repository')
def step_impl(context, file_name):
    issue_dir = context.tempdir + '/.fix/issues/'
    expected_file = Path(issue_dir + file_name)
    assert expected_file.exists()


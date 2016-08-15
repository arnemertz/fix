from behave import *
from pathlib import Path
import requests


@given('an empty Fix repository')
def step_impl(context):
    pass


@when('we create issues')
def step_impl(context):
    table = context.table
    issue_keys = table.headings
    for row in table:
        issue_json = extract_issue_json(issue_keys, row)
        create_issue(issue_json)


@then('an issue file "{file_name}" exists in the repository')
def step_impl(context, file_name):
    issue_dir = context.tempdir + '/.fix/issues/'
    expected_file = Path(issue_dir + file_name)
    assert expected_file.exists()


def extract_issue_json(issue_keys, row):
    issue_data = {}
    for key in issue_keys:
        issue_data[key] = row[key]
    issue_json = {'data': issue_data}
    return issue_json


def create_issue(issue_json):
    r = requests.post('http://localhost:8080/issue/new', json=issue_json)
    assert r.status_code == 200


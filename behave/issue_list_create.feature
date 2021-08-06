Feature: Creating and listing issues

  Scenario: list issues for an empty repository shows an empty list
    Given an empty issue repository
    When we list all issues
    Then it prints "total: 0 issues"
    And terminates with exit code OK

  @skip
  Scenario: create an issue
    Given an empty issue repository
    When we create an issue titled "My first issue in Fix" with description
    """
    Dorem Fixum dolor sit amet, consectetur adipisicing elit, give me a break
    how much text do you want for a long description
    """
    Then it prints "Issue created: my-fir-iss-in-[hash]"
    And terminates with exit code OK

  @skip
  Scenario: created issues are listed in alphabetic order by ID
    Given an empty issue repository
    When we create an issue titled "The first created issue" with description
    """
    This is a boilerplate issue description
    """
    And we create an issue titled "Another issue for this test"
    And we create an issue titled "Third issue"
    And we list all issues
    Then it prints a list of issues
      | issue ID prefix | title                       | status |
      | ano-iss-for-thi | Another issue for this test | open   |
      | the-fir-cre-iss | The first created issue     | open   |
      | thi-iss-yyy-zzz | Third issue                 | open   |
    And it prints "total: 3 issues"

  @skip
  Scenario: creation of identical issues is rejected
    Given an empty issue repository
    When we create an issue titled "A unique issue" with description
    """
    A unique description
    """
    Then it prints "Issue created: a-uni-iss-zzz-[hash]"
    And terminates with exit code OK
    When we create an issue titled "A unique issue" with description
    """
    A unique description
    """
    Then it prints "Issue already exists: a-uni-iss-zzz-[hash]"
    And terminates with exit code ERROR

  @skip
  Scenario: creation of issues with identical title but different description is allowed
    Given an empty issue repository
    When we create an issue titled "A unique issue" with description
    """
    A unique description
    """
    Then it prints "Issue created: a-uni-iss-zzz-[hash]"
    When we create an issue titled "A unique issue" with description
    """
    A quite different description
    """
    Then it prints "Issue created: a-uni-iss-zzz-[hash]"
    And terminates with exit code OK
    When we list all issues
    Then it prints a list of 2 issues
      | issue ID prefix | title          | status |
      | a-uni-iss-zzz   | A unique issue | open   |
      | a-uni-iss-zzz   | A unique issue | open   |

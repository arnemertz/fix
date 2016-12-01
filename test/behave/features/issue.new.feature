Feature: creating new issues

  Scenario: create first issue
    Given an empty Fix repository
    When we create issues
        | summary      | description  |
        | First issue  | A serious problem: the issue database was empty! |
    Then an issue file "1.json" exists in the repository
    And the response has http code 200

  Scenario: new issues get assigned increasing IDs
    Given a Fix repository with issues
        | ID | summary       | description |
        | 1  | First issue   | Issue number one.  |
        | 7  | A Later issue | There will be more |
    Then an issue file "7.json" exists in the repository
    But an issue file "8.json" does not exist in the repository
    When we create issues
        | summary      | description    |
        | A new issue  | I told you!    |
        | Yet another  | There's more!  |
    Then an issue file "8.json" exists in the repository
    And an issue file "9.json" exists in the repository
    And the response has http code 200

  Scenario: new issue requests may not contain IDs
    Given a Fix repository
    When we create an issue
        | summary | description | ID |
        | Issue   | with ID     | 22 |
    Then the response has http code 400

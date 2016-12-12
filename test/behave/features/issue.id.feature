Feature: show details of a single issue

  Scenario: Empty repository
    Given an empty Fix repository
    When we query the issue with ID 42
    Then the response has http code 404

  Scenario: Issue does not exist
    Given a Fix repository with issues
      | ID | summary       | description |
      | 1  | First issue   | Issue number one.  |
      | 7  | A Later issue | There will be more |
    When we query the issue with ID 4
    Then the response has http code 404

  Scenario: Issue exists
    Given a Fix repository with issues
      | ID | summary       | description |
      | 1  | First issue   | Issue number one.  |
      | 7  | A Later issue | There will be more |
    When we query the issue with ID 7
    Then the response has http code 200
    And the response is an object
      | ID | summary       | description |
      | 7  | A Later issue | There will be more |

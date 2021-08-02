Feature: Fix CLI behavior

  Scenario: Show usage when called without arguments
    When we call Fix without arguments
    Then it prints usage information
    And it prints a list of available commands
    And terminates with exit code 1

  Scenario: Show usage when called with help option
    When we call Fix with argument list "--help"
    Then it prints usage information
    And it prints a list of available commands
    And terminates with exit code 0

  @skip
  Scenario Outline: Show error when called with an unknown argument
    When we call Fix with argument list "<args>"
    Then it prints "fix: '<arg1>' is not a fix command. See 'fix --help'."
    And terminates with exit code 1

  Examples:
      | args         | arg1  |
      | foo          | foo   |
      | bar baz      | bar   |

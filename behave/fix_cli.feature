Feature: Fix CLI behavior

  @wip
  Scenario: Show usage when called without arguments
    When we call Fix without arguments
    Then it prints usage information
    And it prints a list of available commands
    And terminates with exit code ERROR

  Scenario: Show usage when called with help option
    When we call Fix with argument list "--help"
    Then it prints usage information
    And it prints a list of available commands
    And terminates with exit code OK

  Scenario Outline: Show error when called with an unknown argument
    When we call Fix with argument list "<args>"
    Then it prints "fix: unknown subcommand. See 'fix --help'."
    And terminates with exit code ERROR

    Examples:
      | args    |
      | foo     |
      | bar baz |

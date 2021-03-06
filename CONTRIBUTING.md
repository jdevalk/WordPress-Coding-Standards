Ongoing development will be done in the `develop` with merges done into `master`
once considered stable.

### Unit Testing

TL;DR

Make sure you have `phpunit` installed and available in your `PATH`.

~~~text
$ mkdir phpcs
$ cd phpcs
$ git clone git@github.com:squizlabs/PHP_CodeSniffer.git .
$ git checkout 1.4.4
$ git clone git@github.com:x-team/WordPress-Coding-Standards.git CodeSniffer/Standards/WordPress
$ phpunit --filter WordPress tests/AllTests.php
~~~

Expected output:

~~~text
PHPUnit 3.7.18 by Sebastian Bergmann.

...............

Time: 1 second, Memory: 37.00Mb

OK (15 tests, 0 assertions)
~~~

You can ignore any skipped tests as these are for `PHP_CodeSniffer` external tools.

The reason why we need to checkout from `PHP_CodeSniffer` git repo to run the tests is because
PEAR installation is intended for ready-to-use not for development. At some point `WordPress-Coding-Standards`
might be submitted to `PHP_CodeSniffer` repo and using their existing convention for unit tests
will eventually help them to test the code before merging in.

#### Unit Testing conventions

If you see inside the `WordPress/Tests`, the structure mimics the `WordPress/Sniffs`. For example,
the `WordPress/Sniffs/Arrays/ArrayDeclarationSniff.php` sniff has unit test class defined in
`WordPress/Tests/Arrays/ArrayDeclarationUnitTest.php` that check `WordPress/Tests/Arrays/ArrayDeclarationUnitTest.inc`
file. See the file naming convention? Lets take a look what inside `ArrayDeclarationUnitTest.php`:

~~~php
...
class WordPress_Tests_Arrays_ArrayDeclarationUnitTest extends AbstractSniffUnitTest
{
    public function getErrorList()
    {
        return array(
                3 => 1,
                7 => 1,
                9 => 1,
                16 => 1,
                31 => 2,
               );

    }//end getErrorList()
}
...
~~~

Also note the class name convention. The method `getErrorList` MUST return an array of line numbers
indicating errors (when running `phpcs`) found in `WordPress/Tests/Arrays/ArrayDeclarationUnitTest.inc`.
If you run:

~~~text
$ cd /path-to-cloned/phpcs
$ ./scripts/phpcs --standard=Wordpress -s CodeSniffer/Standards/WordPress/Tests/Arrays/ArrayDeclarationUnitTest.inc
...
--------------------------------------------------------------------------------
FOUND 8 ERROR(S) AND 2 WARNING(S) AFFECTING 6 LINE(S)
--------------------------------------------------------------------------------
  3 | ERROR   | Array keyword should be lower case; expected "array" but found
    |         | "Array" (WordPress.Arrays.ArrayDeclaration)
  7 | ERROR   | There must be no space between the Array keyword and the
    |         | opening parenthesis (WordPress.Arrays.ArrayDeclaration)
  9 | ERROR   | Empty array declaration must have no space between the
    |         | parentheses (WordPress.Arrays.ArrayDeclaration)
 12 | WARNING | No space after opening parenthesis of array is bad style
    |         | (WordPress.Arrays.ArrayDeclaration)
 12 | WARNING | No space before closing parenthesis of array is bad style
    |         | (WordPress.Arrays.ArrayDeclaration)
 16 | ERROR   | Each line in an array declaration must end in a comma
    |         | (WordPress.Arrays.ArrayDeclaration)
 31 | ERROR   | Expected 1 space between "'type'" and double arrow; 0 found
    |         | (WordPress.Arrays.ArrayDeclaration)
 31 | ERROR   | Expected 1 space between double arrow and "'post'"; 0 found
    |         | (WordPress.Arrays.ArrayDeclaration)
 31 | ERROR   | Expected 1 space before "=>"; 0 found
    |         | (WordPress.WhiteSpace.OperatorSpacing)
 31 | ERROR   | Expected 1 space after "=>"; 0 found
    |         | (WordPress.WhiteSpace.OperatorSpacing)
--------------------------------------------------------------------------------
....
~~~

You'll see the line number and number of ERRORs we need to return in `getErrorList` method.
In line #31 there are two ERRORs belong to `WordPress.WhiteSpace.OperatorSpacing` sniff and
it MUST not included in `ArrayDeclarationUnitTest` (that's why we only return 2 errros for line #31).
Also there's `getWarningList` method in unit test class that returns an array of line numbers
indicating WARNINGs.

<?php

function myTemplateTags() {} // Bad, using camel caps

function my_template_tags() {} // Good

function _my_template_tags() {} // OK

function __my_template_tags() {} // OK

class My_Plugin {

	public static function __my_init() {} // Bad, only PHP magic methods should be prefixed with double underscore

	public function myInit() {} // Bad

	public static function _my_init() {} // OK

	public function my_init() {} // OK
}
// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Js_dict = require("bs-platform/lib/js/js_dict.js");

var query = "query allCountries {\n  countries {\n    name\n    emoji\n    code\n  }\n}";

var payload = { };

payload["query"] = query;

console.log(JSON.stringify(payload));

var value = Js_dict.get(payload, "query");

console.log(value);

exports.query = query;
exports.payload = payload;
exports.value = value;
/*  Not a pure module */
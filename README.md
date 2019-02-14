
# ReasonML and Graphql without Graphql

Graphql Queries with Bs-Axios and Bs-Fetch

![](https://cdn-images-1.medium.com/max/2000/1*GuKhYjEAWofmWHxKzknFhQ.jpeg)

Setting it up:

<iframe src="https://medium.com/media/a57657dcd6d5b10cd2fbd9e3257b8c1b" frameborder=0></iframe>

## Graphql

If you didn’t know about graphql you probably would not be here so lets assume you know about. The thing we want to focus on here is that a graphql query, in its simplest form, is just some JSON that returns JSON. So if we know how to make an HTTP call to a graphql endpoint then we know how to get data. Now you want to be albe to read the response. In graphql, the response can look crazy sometimes. That’s why there are great reason graphql client’s out there like [reason-apollo](https://github.com/apollographql/reason-apollo), [reason-urql](https://github.com/FormidableLabs/reason-urql) and others. We will be using the mother of all clients, [bs-fetch](https://github.com/reasonml-community/bs-fetch). Bs-Fetch is just simple http transport for ReasonML projects. It will return json.

Here is the json you will get back using another client, [cURL](https://curl.haxx.se/).

Open your terminal and run:

<iframe src="https://medium.com/media/de156937d8904ee4c7f96962b9e19d17" frameborder=0></iframe>

Or just go to [https://countries.trevorblades.com/](https://countries.trevorblades.com/) and add this query to the left side of the screen.

<iframe src="https://medium.com/media/f1e1820824819fc0910b03032154af8b" frameborder=0></iframe>

## Preparing Our Query

Incidentally, this is how I learn this stuff or work through projects. I get the simplest thing to work then move on. Then I write a blog post about it so that I don’t forget, uh, I mean, so I can give back to the amazing [ReasonML Community](https://reasonml.github.io/docs/en/community) which has given me so much mentoring. Check it out.

In src/Demo we want to write a function that will prepare our query to be passed as a payload to the fetch client.

Let’s call the function prepareQuery. Remember that graphql queries are json turned into strings to go across http. We need to duplicate that in our reason code so that a graphql client will understand it. We already know what we got back from trying the query in Graphiql and with cURL. We in reason is a string and this looks like we are turning a string into Json and back into a string so that its in the correct format for the graphql server which is recieving it. Graphql queries are NOT strings. They are strings constructed from JSON.

Here is our query set to a simple string in our reason code.

<iframe src="https://medium.com/media/518a378db6c6367da7bde61002bad137" frameborder=0></iframe>

Making this query usable for a graphql server, is a three step process when we do it by hand like we are doing now.

## Converting Our Query string to a JS object

We need to convert the string into a javascript object. We do that using [Js.Dict](https://bucklescript.github.io/bucklescript/api/Js.Dict.html#TYPEt) which says that it is of Dictionary type (ie an '{ }' JS object). I guess '{}' means dictionary in OCaml. Seems like its supposed to be self explanatory to me. Maybe one day it will be.

Js.Dict has an empty method which have to use to create a dictionary which will give us our Js.Object. Since our query string is going to be the payload recieved by the graphql server, lets call it payload. Write this under your query string in src/Demo:

<iframe src="https://medium.com/media/cbdd5dd6fc926caa42778b84ff1c14dd" frameborder=0></iframe>

If you run the file, you see that payload logs {} which is an empty js object as the docs told us.

To add some our string to that empty object we use [Js.Dict.set](https://bucklescript.github.io/bucklescript/api/Js.Dict.html#VALset) which has this signature:

<iframe src="https://medium.com/media/9ed721718a4889c9e2b938b9bb1d6652" frameborder=0></iframe>

So that means we need to call Js.Dict.set and pass it a dictionary type, a key we want to set and the string to set that keys value to.

Let’s try this, where payload is of Dict type because we created it a second ago as an empty Js.Dict type:

<iframe src="https://medium.com/media/115f8d567b46b4858ca22dbf539b6910" frameborder=0></iframe>

The second paramater, is our key which we are callinq query, and finally the third paramater is the actual value we want set to that key.

Run node src/Demo.bs.js again and you should see this:

<iframe src="https://medium.com/media/7f18960ec966991cf82ccee907a33a2f" frameborder=0></iframe>

That’s our key and key value in our payload Js Object! Let compare that with what was passed in our curl command since we know that works. Let's take another look at the data-binary key from our curl statement before since we know that works:

<iframe src="https://medium.com/media/f9245c45d1399c6333a786d818c5ccec" frameborder=0></iframe>

We still have a proper js object but we need to turn it into a stringified JSON Object which is what we are looking at in the curl query. The curl quert format is what the graphql server is expecting.

Let’s hit the bucklescript docs.

From the bucklescript api, [Js.Json.string](https://bucklescript.github.io/bucklescript/api/Js.Json.html#VALstring) in **string s makes a JSON string of the string s**.

We already made a JSON string of our string when we set our value in our payload Dict.

Again, from the bucklescript api, [Js.Json.object_](https://bucklescript.github.io/bucklescript/api/Js.Json.html#VALobject) in **object_ dict makes a JSON object of the Js.Dict.t dict**.

Let’s call Js.Json.object_ on our Js.Dict value to see what that looks like.

Add Js.log(Js.Json.object_(payload)); to your file. It should look like this now:

<iframe src="https://medium.com/media/967a7858f98453b510ada7f04e988f0b" frameborder=0></iframe>

What do we get when we run the file?

<iframe src="https://medium.com/media/5d0d7fcbe641de95e18be66a69fcaaad" frameborder=0></iframe>

Compare to curl:

<iframe src="https://medium.com/media/cec49aa1b6b032e3be2ce8c3f923e1fc" frameborder=0></iframe>

That doesn’t look like it did anything.

At this point, I go into the docs lookin for stringify in Js.Dict Api. It's not there. I find it in [Js.Json](https://bucklescript.github.io/bucklescript/api/Js.Json.html#ValString) with a great example:

<iframe src="https://medium.com/media/a50ba9a4ca954700696f10740f9fb550" frameborder=0></iframe>

Without even really studying the example my eyes jump the last line where they are calling Js.Json.stringify on the result of calling Js.Json.object_ on the dict value. That seems counter intuitive to me because we already call Js.Json.string on our query string when we put it in. Let's reread the docs.

Js.Json.string makes a JSON string of our query string.

Js.Json.stringify **formats** the JSON data structure as a string, that's our payload object,

Let’s see what we get when we stringify our Js.Json.object_(payload).

Add this to src/Demo.re:

<iframe src="https://medium.com/media/11623ec9f82642653e1935f033716ccd" frameborder=0></iframe>

<iframe src="https://medium.com/media/72d0b25e4295110d56003861374f2ebd" frameborder=0></iframe>

Compare to curl:

<iframe src="https://medium.com/media/8478e593664ccd75e0b9a1d68b9e5401" frameborder=0></iframe>

That looks exactly the same. You could copy your output to the curl statement and run it and should work.

So how do you call this query in your program? Run:

    $ yarn add bs-fetch
    $ jq '.["bs-dependencies"] += ["bs-fetch"]' bsconfig.json | sponge bsconfig.json

If you don’t have jq installed be sure to manually add bs-fetch to your bs-dependencies in bsconfig.json. It should look like this:

    "bs-dependencies": ["bs-fetch"],

Click the little blue “Console” icon in the codesandbox embed to see the results.

<iframe src="https://medium.com/media/a3032a264162fc954d425c34b3029517" frameborder=0></iframe>

### GraphQL/Bs-Axios in ReasonML

And here it is using Axios. This is way more of a hack and bound to be error prone, because of the way I formatted the `query` string to get it ready to be read as a json object. But it works!

<iframe src="https://medium.com/media/03882187b9fa8ae88e8d14ed0e9899ce" frameborder=0></iframe>

And here is a less sloppy way to do it with Axios so you dont have to worry about hand formatting your string. You add [Magnus Hallin](undefined)’s [graphql_ppx](https://github.com/mhallin/graphql_ppx) package to your dev dependencies. Then a ppx-flags key to your bsconfig.json.

    $ yarn add graphql_ppx -D

    Then add this to bsconfig.json `"ppx-flags":["graphql_ppx/ppx"],`

Now we change our Axios query to this:

<iframe src="https://medium.com/media/59ad16d18f5959b79b62c38583cd8cc9" frameborder=0></iframe>

Much cleaner, safer and much less nerve racking.

Note the isomorphic-fetch import. That let’s you run the file in place with node.js and without starting a server accessing a browser for http…

Here it is in codesandbox but it does run because codesandbox apparently can’t handle the graphql_ppx import without additional configuration.

[https://codesandbox.io/s/kwz39o14nr](https://codesandbox.io/s/kwz39o14nr)

Thanks for reading. Hope this helps.

Any Questions? Anyone? Anyone?

![[https://en.wikipedia.org/wiki/Ferris_Bueller%27s_Day_Off](https://en.wikipedia.org/wiki/Ferris_Bueller%27s_Day_Off)](https://cdn-images-1.medium.com/max/2000/1*rtr-mg0P9-hVMHvlZ0kSFg.jpeg)*[https://en.wikipedia.org/wiki/Ferris_Bueller%27s_Day_Off](https://en.wikipedia.org/wiki/Ferris_Bueller%27s_Day_Off)*



let query = "query allCountries {
  countries {
    name
    emoji
    code
  }
}";


let payload = Js.Dict.empty();
Js.Dict.set(payload, "query",Js.Json.string(query));
Js.Json.stringify(Js.Json.object_(payload)) |> Js.log;
let value = Js.Dict.get(payload, "query");
Js.log(value)

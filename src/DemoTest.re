[%raw "require('isomorphic-fetch')"];
open Fetch;

let query = "{dogs {
    name
    breed
    description
  }}";

let payload = Js.Dict.empty();
Js.Dict.set(payload, "query",Js.Json.string(query));
  Js.Promise.(
    fetchWithInit(
      "https://formidadog-ql.now.sh/graphql",
      RequestInit.make(
        ~method_=Post,
        ~headers=HeadersInit.make({
          "Content-Type": "application/json"
        }),
        ~body=BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
        ()
      ),
    )
    |> then_(Response.json)
    |> then_(json => {
      Js.log2("JSON",json);
      }
    |> resolve
                   )
    |> catch(err =>
                   Js.Promise.resolve(Js.log(err))
                 )
    |> ignore
);
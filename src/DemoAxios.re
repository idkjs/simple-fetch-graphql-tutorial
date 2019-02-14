let query ="{" ++ {j|dogs {
    name
    breed
    description
  }|j} ++"}";

    Axios.get("https://formidadog-ql.now.sh/graphql?query="++query)
    |> Js.Promise.then_(value => {
     let dogs = value##data;
     Js.log2("Dogs", value##data);
     Js.Promise.resolve(dogs);
   })
|> Js.Promise.catch(err => {
     Js.log2("Something went wrong!", err);
     Js.Promise.resolve(err);
})

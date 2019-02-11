let component = ReasonReact.statelessComponent("FetchExample");

let make = (_children) => {
  ...component,
  render: (_self) =>
  <div>
        <h1> (ReasonReact.string("Countries")) </h1>
        <p> (ReasonReact.string("Graphiql: "))
        <a href="https://countries.trevorblades.com/">
          (ReasonReact.string("https://countries.trevorblades.com/"))
        </a> </p>
        <p> (ReasonReact.string("Source: "))
        <a href="https://github.com/trevorblades/countries">
          (ReasonReact.string("https://github.com/trevorblades/countries"))
        </a> </p>
    </div>
};
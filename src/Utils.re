/* Access the global value __dirname and we want it to be available under the name __dirname in our Reason code.
      Since the name of our Reason alias for the value is the same as the value name in Node,
      we can keep the string body empty as a shorthand to achieve the same thing
   */
[@bs.val] external __dirname: string = "";
let getAbsolutePath = (path: string) => {
  Node.Path.resolve(__dirname, path);
};

let padText = (padding: int, text: string) => {
  String.make(padding, ' ') ++ text;
};

/* Helper function to filter a list of directory items based on a name to ignore */
let filterItemsList = (~ignore=?, itemsList: list(Fs.dirent)) => {
  switch (ignore) {
  | None => itemsList

  | Some(nameToIgnore) =>
    itemsList
    |> List.filter(item => !item##isDirectory() || item##name != nameToIgnore)
  };
};

let rec printDir = (~padding: int, ~ignore=?, ~dirPath: string) => {
  let absolutePath = getAbsolutePath(dirPath);

  /* Notice that when create options with withFileTypes specified,
        we need to pass () as the second parameter. This is required
        by Reason since withFileTypes is the only argument and it’s optional.
     */
  let options = Fs.readdirSyncOptions(~withFileTypes=true, ());

  Fs.readdirSync(absolutePath, options)
  |> Array.to_list
  |> filterItemsList(~ignore?)
  |> List.iter((item: Fs.dirent) =>
       if (!item##isDirectory()) {
         {js|📄|js} ++ " " ++ item##name |> padText(padding) |> Js.log;
       } else {
         {js|📁|js} ++ " " ++ item##name |> padText(padding) |> Js.log;

         printDir(
           ~padding=padding + 1,
           ~ignore?,
           ~dirPath=absolutePath ++ "/" ++ item##name,
         );
       }
     );
};

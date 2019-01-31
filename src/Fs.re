/* Reason, however, provides an easy way to create object bindings out of
     Record types, by using [@bs.deriving abstract] followed by the Record

     We can make withFileTypes attribute optional when creating an options
     object for readdirSync by prefixing the attribute with[@bs.optional]
   */
[@bs.deriving abstract]
type readdirSyncOptions = {
  [@bs.optional]
  withFileTypes: bool,
};

/* example of a Reason Js.t object */
type dirent = {
  .
  "name": string,
  [@bs.meth] "isDirectory": unit => bool /* method */
};

/* Binding to the method of node fs module */
[@bs.module "fs"]
external readdirSync: (string, readdirSyncOptions) => array(dirent) = "";

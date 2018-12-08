/* file: src/Action.re

     Extracted from:
     https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-react/src/OrderForm.re
   */
type t =
  | CommitOrder
  | ChangeQty(string)
  | ChangeSize(string)
  | ChangeSleeve(string)
  | ChangeColor(string)
  | ChangePattern(string)
  | Delete(int);

/* file: src/Order.re

     Extracted from:
     https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-react/src/Shirt.re
   */
type t = {
  orderNumber: int,
  quantity: int,
  size: Shirt.Size.t,
  sleeve: Shirt.Sleeve.t,
  color: Shirt.Color.t,
  pattern: Shirt.Pattern.t,
};

let empty = {
  orderNumber: 0,
  quantity: 0,
  size: Shirt.Size.Medium,
  sleeve: Shirt.Sleeve.Long,
  color: Shirt.Color.White,
  pattern: Shirt.Pattern.Solid,
};

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

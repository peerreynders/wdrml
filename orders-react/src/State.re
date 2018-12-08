/* file: src/State.re

     Extracted from:
     https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-react/src/OrderForm.re
   */
type orderCollection = array(Order.t);
type errorInfo = option(string);

type editInfo = {
  qty: string,
  size: string,
  sleeve: string,
  color: string,
  pattern: string,
};

type orderInfo = {orderNumber: int};

type t = {
  edit: editInfo,
  current: orderInfo,
  orders: orderCollection,
  error: errorInfo,
};

let emptyState = () => {
  let edit: editInfo = {
    qty: "1",
    size: "M",
    sleeve: "Long sleeve",
    color: "White",
    pattern: "Solid",
  };
  let current = {orderNumber: 1};
  let orders = [||];
  let error = None;

  {edit, current, orders, error};
};

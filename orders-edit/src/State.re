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
  actionLabel: string,
};

type orderInfo = {
  orderNumber: int,
  editNumber: option(int),
};

type t = {
  edit: editInfo,
  current: orderInfo,
  orders: orderCollection,
  error: errorInfo,
};

let emptyEdit: editInfo = {
  qty: "",
  size: "",
  sleeve: "",
  color: "",
  pattern: "",
  actionLabel: "Add",
};

let editFromOrder: (Order.t, ~actionLabel: string=?, unit) => editInfo =
  (order, ~actionLabel="Add", ()) => {
    qty: string_of_int(order.quantity),
    size: Shirt.Size.toString(order.size),
    sleeve: Shirt.Sleeve.toString(order.sleeve),
    color: Shirt.Color.toString(order.color),
    pattern: Shirt.Pattern.toString(order.pattern),
    actionLabel,
  };

let emptyState = {
  let edit = emptyEdit;
  let current = {orderNumber: 1, editNumber: None};
  let orders = [||];
  let error = None;

  {edit, current, orders, error};
};

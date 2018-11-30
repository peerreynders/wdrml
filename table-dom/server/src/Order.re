/* Original:
     https://media.pragprog.com/titles/reasonml/code/records/shirt-stats/src/Stats.re
   */

type t = {
  quantity: int,
  size: Shirts.Size.t,
  sleeve: Shirts.Sleeve.t,
  color: Shirts.Color.t,
  pattern: Shirts.Pattern.t,
  cuff: Shirts.Cuff.t,
  collar: Shirts.Collar.t,
};

let makeEmpty: unit => t =
  () => {
    quantity: 0,
    size: Small,
    sleeve: Short,
    color: White,
    pattern: Solid,
    cuff: Button,
    collar: Straight,
  };

let quantitySet: (t, int) => t = (order, quantity) => {...order, quantity};
let sizeSet: (t, Shirts.Size.t) => t = (order, size) => {...order, size};
let sleeveSet: (t, Shirts.Sleeve.t) => t =
  (order, sleeve) => {...order, sleeve};
let colorSet: (t, Shirts.Color.t) => t = (order, color) => {...order, color};
let patternSet: (t, Shirts.Pattern.t) => t =
  (order, pattern) => {...order, pattern};
let cuffSet: (t, Shirts.Cuff.t) => t = (order, cuff) => {...order, cuff};
let collarSet: (t, Shirts.Collar.t) => t =
  (order, collar) => {...order, collar};

let sizeGet: t => Shirts.Size.t = order => order.size;
let colorGet: t => Shirts.Color.t = order => order.color;
let sleeveGet: t => Shirts.Sleeve.t = order => order.sleeve;
let patternGet: t => Shirts.Pattern.t = order => order.pattern;
let collarGet: t => Shirts.Collar.t = order => order.collar;
let cuffGet: t => Shirts.Cuff.t = order => order.cuff;

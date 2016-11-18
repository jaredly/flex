open LayoutTypes;

open LayoutSupport;

open LayoutValue;

let shouldFilter = true;

let indent n =>
  for i in 0 to (n - 1) {
    print_string "  "
  };

let print_number_0 (indentNum, str, number) =>
  if (not shouldFilter || not (number == zero)) {
    indent indentNum;
    Printf.printf "%s: %s,\n" str (scalarToString number)
  };

let print_number_nan (indentNum, str, number) =>
  if (not shouldFilter || not (isUndefined number)) {
    indent indentNum;
    Printf.printf "%s: %s,\n" str (scalarToString number)
  };

let layoutStr layout =>
  "{left:" ^
  scalarToString layout.left ^
  ", top:" ^
  scalarToString layout.top ^
  ", width:" ^ scalarToString layout.width ^ ", height:" ^ scalarToString layout.height ^ "}";

let rec printCssNodeRec (node, options, level) => {
  indent level;
  Printf.printf "{\n";
  switch node.print {
  | None => ()
  | Some printer => printer node.context
  };
  if options.printLayout {
    indent (level + 1);
    Printf.printf "layout: {\n";
    print_number_nan (level + 2, "width", node.layout.width);
    print_number_nan (level + 2, "height", node.layout.height);
    print_number_nan (level + 2, "measuredWidth", node.layout.measuredWidth);
    print_number_nan (level + 2, "measuredHeight", node.layout.measuredHeight);
    print_number_0 (level + 2, "top", node.layout.top);
    print_number_0 (level + 2, "left", node.layout.left);
    /* indent (level + 2); */
    /* Printf.printf "shouldUpdate: %b,\n" node.layout.shouldUpdate; */
    /* print_number_0 (level + 2, "generationCount", float_of_int node.layout.generationCount); */
    indent (level + 1);
    Printf.printf "},\n"
  };
  if options.printStyle {
    indent (level + 1);
    Printf.printf "style: {\n";
    indent (level + 2);
    switch node.style.justifyContent {
    | CssJustifyFlexStart => Printf.printf "justify: 'start',\n"
    | CssJustifyCenter => Printf.printf "justify: 'center',\n"
    | CssJustifyFlexEnd => Printf.printf "justify: 'flexend',\n"
    | CssJustifySpaceBetween => Printf.printf "justify: 'speceBetween',\n"
    | CssJustifySpaceAround => Printf.printf "justify: 'speceAround',\n"
    };
    if (node.style.flexDirection == CssFlexDirectionColumn) {
      indent (level + 2);
      Printf.printf "flexDirection: 'column',\n"
    } else if (
      node.style.flexDirection == CssFlexDirectionColumnReverse
    ) {
      indent (level + 2);
      Printf.printf "flexDirection: 'column-reverse',\n"
    } else if (
      node.style.flexDirection == CssFlexDirectionRow
    ) {
      indent (level + 2);
      Printf.printf "flexDirection: 'row',\n"
    } else if (
      node.style.flexDirection == CssFlexDirectionRowReverse
    ) {
      indent (level + 2);
      Printf.printf "flexDirection: 'row-reverse',\n"
    };
    if (node.style.justifyContent == CssJustifyCenter) {
      indent (level + 2);
      Printf.printf "justifyContent: 'center',\n"
    } else if (
      node.style.justifyContent == CssJustifyFlexEnd
    ) {
      indent (level + 2);
      Printf.printf "justifyContent: 'flex-end',\n"
    } else if (
      node.style.justifyContent == CssJustifySpaceAround
    ) {
      indent (level + 2);
      Printf.printf "justifyContent: 'space-around',\n"
    } else if (
      node.style.justifyContent == CssJustifySpaceBetween
    ) {
      indent (level + 2);
      Printf.printf "justifyContent: 'space-between',\n"
    };
    if (node.style.alignItems == CssAlignCenter) {
      indent (level + 2);
      Printf.printf "alignItems: 'center',\n"
    } else if (
      node.style.alignItems == CssAlignFlexEnd
    ) {
      indent (level + 2);
      Printf.printf "alignItems: 'flex-end',\n"
    } else if (
      node.style.alignItems == CssAlignStretch
    ) {
      indent (level + 2);
      Printf.printf "alignItems: 'stretch',\n"
    };
    if (node.style.alignContent == CssAlignCenter) {
      indent (level + 2);
      Printf.printf "alignContent: 'center',\n"
    } else if (
      node.style.alignContent == CssAlignFlexEnd
    ) {
      indent (level + 2);
      Printf.printf "alignContent: 'flex-end',\n"
    } else if (
      node.style.alignContent == CssAlignStretch
    ) {
      indent (level + 2);
      Printf.printf "alignContent: 'stretch',\n"
    };
    if (node.style.alignSelf == CssAlignFlexStart) {
      indent (level + 2);
      Printf.printf "alignSelf: 'flex-start',\n"
    } else if (
      node.style.alignSelf == CssAlignCenter
    ) {
      indent (level + 2);
      Printf.printf "alignSelf: 'center',\n"
    } else if (
      node.style.alignSelf == CssAlignFlexEnd
    ) {
      indent (level + 2);
      Printf.printf "alignSelf: 'flex-end',\n"
    } else if (
      node.style.alignSelf == CssAlignStretch
    ) {
      indent (level + 2);
      Printf.printf "alignSelf: 'stretch',\n"
    };
    print_number_nan (level + 2, "flex", LayoutSupport.cssNodeStyleGetFlex node);
    if (node.style.overflow == Hidden) {
      indent (level + 2);
      Printf.printf "overflow: 'hidden',\n"
    } else if (
      node.style.overflow == Visible
    ) {
      indent (level + 2);
      Printf.printf "overflow: 'visible',\n"
    } else {
      indent (level + 2);
      Printf.printf "overflow: 'scroll',\n"
    };
    print_number_0 (level + 2, "marginLeft", node.style.marginLeft);
    print_number_0 (level + 2, "marginRight", node.style.marginRight);
    print_number_0 (level + 2, "marginTop", node.style.marginTop);
    print_number_0 (level + 2, "marginBottom", node.style.marginBottom);
    print_number_0 (level + 2, "paddingLeft", node.style.paddingLeft);
    print_number_0 (level + 2, "paddingRight", node.style.paddingRight);
    print_number_0 (level + 2, "paddingTop", node.style.paddingTop);
    print_number_0 (level + 2, "paddingBottom", node.style.paddingBottom);
    print_number_0 (level + 2, "borderLeftWidth", node.style.borderLeft);
    print_number_0 (level + 2, "borderRightWidth", node.style.borderRight);
    print_number_0 (level + 2, "borderTopWidth", node.style.borderTop);
    print_number_0 (level + 2, "borderBottomWidth", node.style.borderBottom);
    print_number_nan (level + 2, "borderStartWidth", node.style.borderStart);
    print_number_nan (level + 2, "borderEndWidth", node.style.borderEnd);
    print_number_nan (level + 2, "paddingStart", node.style.paddingStart);
    print_number_nan (level + 2, "paddingEnd", node.style.paddingEnd);
    print_number_nan (level + 2, "marginStart", node.style.marginStart);
    print_number_nan (level + 2, "marginEnd", node.style.marginEnd);
    print_number_nan (level + 2, "width", node.style.width);
    print_number_nan (level + 2, "height", node.style.height);
    print_number_nan (level + 2, "maxWidth", node.style.maxWidth);
    print_number_nan (level + 2, "maxHeight", node.style.maxHeight);
    print_number_nan (level + 2, "minWidth", node.style.minWidth);
    print_number_nan (level + 2, "minHeight", node.style.minHeight);
    if (node.style.positionType == CssPositionAbsolute) {
      indent (level + 2);
      Printf.printf "position: 'absolute', "
    };
    print_number_nan (level + 2, "left", node.style.left);
    print_number_nan (level + 2, "right", node.style.right);
    print_number_nan (level + 2, "top", node.style.top);
    print_number_nan (level + 2, "bottom", node.style.bottom);
    indent (level + 1);
    Printf.printf "},\n"
  };
  if (options.printChildren && Array.length node.children > 0) {
    indent (level + 1);
    Printf.printf "children: [\n";
    for i in 0 to (Array.length node.children - 1) {
      printCssNodeRec (node.children.(i), options, level + 2)
    };
    indent (level + 1);
    Printf.printf "]},\n"
  } else {
    indent level;
    Printf.printf "},%!\n"
  }
};

let printCssNode (node, options) => printCssNodeRec (node, options, 0);

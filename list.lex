NUMBER : ('0'..'9')+
NAME : ('a'..'z' | 'A'..'Z')+
stat : list EOF | assign EOF;
assign : list '=' list;
list : '[' elements ']';
elements : element (',' element)+;
element : NAME | NAME '=' NAME | list;


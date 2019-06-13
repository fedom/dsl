NUMBER : ('0'..'9')+
NAME : ('a'..'z' | 'A'..'Z')+
list : '[' elements ']';
elements : element (',' element)+;
element : NAME | NAME '=' NAME | list;


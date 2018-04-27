//
//  main.c
//  Lager2
//
//  Created by Haubir Mariwani on 4/16/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#include "main.h"

char *menu_string() {
  return "[L]ägg till en vara\n[T]a bort en vara\n[R]edigera en vara\nÅn[g]ra senaste ändringen\nLista [h]ela varukatalogen\n[P]acka en pall\n[A]vsluta\n\nVad vill du göra idag? ";
}


int main(int argc, const char * argv[]) {
  
  tree *main_tree = tree_new();
    
  while (1) {
    char *input_string = calloc(1024, sizeof(char));
    string_entry(menu_string(), input_string);
    
    char *input_string_tolower = calloc(1024, sizeof(char));
    string_to_lower(input_string, input_string_tolower);
    free(input_string);
    
    printf("input_string_tolower: %s\n", input_string_tolower);
    strip_string(input_string_tolower);
    
    if ((string_length(input_string_tolower) > 1) && (string_compare(input_string_tolower, "preset") != 0)){printf("Din input matchade inte något av alternativen från menyn. Försök igen.\n\n");}
    else if (string_compare(input_string_tolower, "l") == 0) {
      printf("Du valde att lägga till en vara\n\n"); 
      test_add_to_tree(main_tree);
    }
    else if (string_compare(input_string_tolower, "t") == 0) {
      printf("Du valde att ta bort en vara\n\n");
      test_remove_node(main_tree);
    }
    else if (string_compare(input_string_tolower, "r") == 0) {
      printf("Du valde att redigera en vara\n\n");
      test_edit_node(main_tree);
    }
    else if (string_compare(input_string_tolower, "g") == 0) {printf("Du valde att ångra den senaste ändringen\n\n");}
    else if (string_compare(input_string_tolower, "h") == 0) {
      printf("Du valde att lista hela varukorgen\n\n");
      tree_list_nodes(main_tree);
    }
    else if (string_compare(input_string_tolower, "p") == 0) {printf("Du valde att packa en pall\n\n");}
    else if (string_compare(input_string_tolower, "a") == 0) {printf("Du valde att avsluta programmet\n\n"); exit(0);}
    else if (string_compare(input_string_tolower, "preset") == 0) {
      printf("Du valde att skapa ett träd med 7 förinställda noder.\n\n");
      tree *new_tree = preset_tree();
      tree_copy(main_tree, new_tree);
      free(new_tree);
    }
    else {printf("Din input matchade inte något av alternativen från menyn. Försök igen.\n\n");}
  }
  
  return 0;
}



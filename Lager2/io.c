//
//  io.c
//  Lager2
//
//  Created by Haubir Mariwani on 5/5/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#include "io.h"

// Only for development purposes. Creates a new tree with 14 nodes. 
tree *preset_tree() {
  char *root_name = string_new();
  root_name = "e";
  tree *new_tree = test_add_root(root_name);
  node **tree_root = tree_get_root(new_tree);
  node *root_node = *tree_root;
  
  char *root_description = string_new();
  root_description = "The letter e.";
  int root_price = 23;
  
  char *root_shelf = string_new();
  root_shelf = "A01";
  int root_shelf_quantity = 9;
  
  ware_set_description(node_get_ware(root_node), root_description);
  ware_set_price(node_get_ware(root_node), root_price);
  ware_increment_shelves(node_get_ware(root_node), root_shelf, root_shelf_quantity);
  
  
  char *list[13] = {"o", "j", "m", "g", "f", "h", "w", "q", "t", "k", "y", "p", "c"};
  char *key_list[13];
  for (int i = 0; i < 13; i++) {
    char *new_key = string_new();
    string_copy(new_key, list[i]);
    key_list[i] = new_key;
  }
  
  char *descript[13] = {"The letter o.", "The letter j.", "The letter m.", "The letter g.", "The letter f.", "The letter h.", "The letter h.", "The letter h.", "The letter h.", "The letter h.", "The letter h.", "The letter h.", "The letter h."};
  char *description_list[13];
  for (int i = 0; i < 13; i++) {
    char *new_description = string_new();
    string_copy(new_description, descript[i]);
    description_list[i] = new_description;
  }
  
  int prices[13] = {4, 17, 99, 3, 2, 47, 55, 67, 78, 89, 90, 22, 31};
  char *shelf_list[13] = {"o11", "j12", "m66", "g78", "f03", "h18", "w39", "q82", "t23", "k21", "y17", "p20", "c91"};
  char *shelf_locations[13];
  int shelf_quantities[13] = {14, 6, 92, 7, 1, 85, 37, 23, 11, 29, 4, 41, 74};
  
  for (int i = 0; i < 13; i++) { 
    node *new_node = node_new();
    ware_set_key(node_get_ware(new_node), key_list[i]);
    ware_set_description(node_get_ware(new_node), description_list[i]);
    ware_set_price(node_get_ware(new_node), prices[i]);
    char *new_shelf = string_new();
    string_copy(new_shelf, shelf_list[i]);
    shelf_locations[i] = new_shelf;
    ware_increment_shelves(node_get_ware(new_node), shelf_locations[i], shelf_quantities[i]);
    node_set_key(new_node, key_list[i]);
    tree_node_add(new_tree, new_node);
  }
  
  return new_tree;
}

void io_list_nodes(tree *input_tree) {
  if (tree_size(input_tree) == 0) {
    printf("Databasen är tom!\n\n");
    return;
  }
  tree_list_nodes(input_tree);
  bool keep_going = string_yes_no_question("Svara ja om du vill se mer information om en vara, annars nej för att återgå till huvudmenyn:");
  if (!keep_going) return;
  
  while (keep_going) {
    int choice = 0;
    while (!io_choose_ware("Vilken vara vill du titta närmre på?", tree_size(input_tree), &choice));
    node *to_show = find_node_by_index(input_tree, choice);
    node_show(to_show);
    keep_going = string_yes_no_question("Vill du se mer information om en annan vara? Om inte, svara 'nej' för att återgå till huvudmenyn.");
    if (keep_going) tree_list_nodes(input_tree);
  }
}

// Only for development purposes. Tests the ability to create a new tree with a root.
tree *test_add_root(char *ware_name) {
  tree *new_tree = tree_new();
  node *new_node = node_new();
  
  if (ware_name == NULL) {
    ware_name = string_new();
    string_entry("Please type a name for the new ware: ", ware_name);
    strip_string(ware_name);
  }
  ware_set_key(node_get_ware(new_node), ware_name);
  node_set_key(new_node, ware_name);
  
  if (tree_node_add(new_tree, new_node)) {
    printf("A node was successfully added to the tree!\n");
    return new_tree;
  }
  else {
    printf("It was not possible to add a node to the test tree...\n");
    free(ware_name);
    return NULL;
  } 
}

// Only for development purposes. Tests the ability to add nodes to a tree.
void io_add_to_tree(tree *input_tree) {
  char *new_key = string_new();
  string_entry("Skriv ett namn för varan: ", new_key);
  char *shelf_location = string_new();
  
  if (find_node_in_tree(new_key, input_tree)) {
    node *existing_node = find_node_in_tree(new_key, input_tree);
    printf("%s finns redan i databasen.\n", new_key);
    char *answer = string_new();
    while (true) {
      string_entry("Vill du lägga till fler av varan?", answer);
      if (string_equals(answer, "ja")) {
        while (!io_add_shelves(input_tree, existing_node, shelf_location, "existing"));
        break;
      }
      if (string_equals(answer, "nej")) {
        free(shelf_location);
        break;
      }
    }
    free(answer);
  }
  else {
    node *new_node = node_new();
    ware_enter_information(node_get_ware(new_node), new_key);
    
    while (!io_add_shelves(input_tree, new_node, shelf_location, "new"));
    
    node_set_key(new_node, ware_get_key(node_get_ware(new_node)));  
    
    if (tree_node_add(input_tree, new_node)) {
      printf("A node was successfully added to the tree!\n");
    }
    else {
      printf("It was not possible to add a node to the tree.....\n");
    }
  }
}

void io_increment_shelves(node *input_node, char *shelf_location, char *flag) {
  int increment = 0;
  int_entry("Hur många styck vill du lägga till?", &increment);
  ware *input_ware = node_get_ware(input_node);
  if (string_equals(flag, "new")) ware_increment_shelves(input_ware, shelf_location, increment);
  if (string_equals(flag, "existing")) {
    shelves_list *input_list = ware_get_shelves(input_ware);
    list_node *node_to_increment = find_list_node_by_shelf_location(input_list, shelf_location);
    shelf *to_increment = (shelf *) list_node_get_data(node_to_increment);
    shelf_increment_quantity(to_increment, increment);
  }
  ware_increment_amount(input_ware, increment);
}

// Checks if the shelf_location follows the correct naming format for shelf locations, and also if the given shelf location is already occupied.
bool io_add_shelves(tree *input_tree, node *input_node, char *shelf_location, char *flag) {
  string_entry("Ange den hyllplats som du vill placera varan på: ", shelf_location);  
  
  if (!is_shelf(shelf_location)) {
    printf("'%s' följer inte rätt format för hyllplatsernas namn. Vänligen ange enligt följande format:\n<Bokstav><Siffra><Siffra>\nT.ex: A01, B23 etc.\n", shelf_location);
    return false;
  }
  
  if (find_shelf_in_tree(shelf_location, input_tree)) {
    if (string_equals(flag, "new")) {
      printf("%s är upptagen, vänligen skriv in en annan hyllplats.\n", shelf_location);
      return false;
    }
    
    if (string_equals(flag, "existing")) {
      char *answer = string_new();
      printf("Varan finns redan på denna hylla. ");
      while (!(string_equals(answer, "ja") || string_equals(answer, "nej"))) {
        string_entry("Vill du utöka antalet på denna hylla?", answer);
        if (string_equals(answer, "ja")) {
          io_increment_shelves(input_node, shelf_location, "existing");
          return true;
        }
        if (string_equals(answer, "nej")) {
          free(shelf_location);
          return true;
        }
        printf("Vänligen svara ja eller nej.\n");
      }
    }
  }
  else {
    io_increment_shelves(input_node, shelf_location, "new");
  }
  
  return true;
}

// Only for development purposes. Tests the ability to remove a node from a tree.
void io_remove_node(tree *input_tree) {
  node *root_node = *(tree_get_root(input_tree));
  
  if (root_node == NULL) {
    printf("Databasen är tom, det finns inget att ta bort!\n");
    return;
  }
  tree_list_nodes(input_tree);
  int choice = 0;
  while (!io_choose_ware("Välj en vara att ta bort.", tree_size(input_tree), &choice));
  
  
  
  node *to_delete = find_node_by_index(input_tree, choice);
  bool keep_going = true;
  while (keep_going) {
    // TODO: Fixa så att man också kan ta bort alla styck av en vara direkt från systemet istället för att behöva ta bort hylla för hylla.
    node_show(to_delete);
    io_remove_shelves(input_tree, to_delete);
    if (!find_node_in_tree(node_get_key(to_delete), input_tree)) break;
    keep_going = string_yes_no_question("Vill du ta bort varan från en annan hylla också?");
  }
  
}

void io_remove_shelves(tree *input_tree, node *input_node) {
  ware *input_ware = node_get_ware(input_node);
  shelves_list *input_shelves = ware_get_shelves(input_ware);
  int shelves_size = shelves_list_get_size(input_shelves);
  int decrement = 0;
  
  if (shelves_size > 1) {
    int choice = 0;
    while (!io_choose_shelves(shelves_size, &choice));
    list_node *to_remove_from = find_list_node_by_index(input_shelves, choice-1);
    shelf *to_decrement = (shelf *) list_node_get_data(to_remove_from);
    
    io_input_decrement(to_decrement, &decrement);
    
    shelf_decrement_quantity(to_decrement, decrement);
    ware_decrement_amount(input_ware, decrement);
    if (shelf_is_empty(to_decrement)) {
      shelves_list_remove_by_index(input_shelves, choice-1);
    }
  }
  else if (shelves_size == 1) {
    list_node *only_list_node = shelves_list_get_first(input_shelves);
    shelf *to_decrement = (shelf *) list_node_get_data(only_list_node);
    
    io_input_decrement(to_decrement, &decrement);
    
    shelf_decrement_quantity(to_decrement, decrement);
    ware_decrement_amount(input_ware, decrement);
    if (shelf_is_empty(to_decrement)) {
      if (tree_node_remove(input_tree, node_get_key(input_node))) {
        printf("Varan är nu borttagen från systemet!\n");
      }
      else {
        printf("It was not possible to remove the node from the tree...\n");
      }
    }
  }
  else {
    printf("test_remove_shelves(): Tried to decrement nonexisting shelves...");
  }
}

void io_input_decrement(shelf *input_shelf, int *decrement) {
  while (true) {
    int_entry("Hur många av varan ska tas bort?", decrement);
    if (*decrement > shelf_get_quantity(input_shelf)) printf("Du kan inte ta bort mer än vad som finns på denna hylla, tänk på att du angav %d vilket är mer än %d!\n", *decrement, shelf_get_quantity(input_shelf));
    else break;
  }
}

bool io_choose_shelves(int shelves_size, int *choice) {
  int_entry("Vilken hyllplats skall tas bort ifrån?", choice);  
  bool valid_choice = false;
  valid_choice = (*choice >= 1) && (*choice <= shelves_size);
  
  if (!valid_choice) {
    printf("Vänligen skriv en siffra mellan 1-%d för att välja en av hyllplatserna.\n", shelves_size);
    return false;
  } 
  
  return true;
}

/* Edits a node in the tree and rebalances the node if necessary */
void io_edit_node(tree *input_tree) {
  if (!tree_get_root(input_tree)) return;
  
  node *tree_root = *(tree_get_root(input_tree));
  
  if (tree_root == NULL) {
    printf("There are no nodes in the tree to edit...\n");
    return;
  }
  
  tree_list_nodes(input_tree);
  int choice = 0;
  while (!io_choose_ware("Vilken vara önskar du att redigera?", tree_size(input_tree), &choice));
  node *to_edit = find_node_by_index(input_tree, choice);
  
  
  if (!to_edit) {
    printf("The node to edit was not found in the tree...\n");
    return; // The node to edit was not found
  }
  else {    
    node *copy_of_edited = node_new();
    node_copy(copy_of_edited, to_edit);
    
    set_left_node(copy_of_edited, NULL);
    set_right_node(copy_of_edited, NULL);
    set_parent_node(copy_of_edited, NULL);
    
    if (io_node_edit(input_tree, copy_of_edited)) { 
      tree_node_remove(input_tree, node_get_key(to_edit));
      tree_node_add(input_tree, copy_of_edited);
    }
    else node_free(copy_of_edited);
  }
}

// TODO!!!
/// - Först ska nodens info visas på skärmen.
/// - Sedan ska användaren få välja vilket attribut den vill ändra
///
/// \returns: true
bool io_node_edit(tree *input_tree, node *input_node) {
  char *answer = string_new();
  
  node_show(input_node);
  string_entry("Svara med 1-5 för att välja ett av alternativen eller skriv \"avsluta\" för att avsluta och återvända till huvudmenyn.\n1. Redigera namn\n2. Redigera beskrivning\n3. Redigera pris\n4. Redigera antal\n5. Redigera hyllplats(er)", answer);
  while ((string_compare(answer, "1") != 0) &&
         (string_compare(answer, "2") != 0) &&
         (string_compare(answer, "3") != 0) &&
         (string_compare(answer, "4") != 0) &&
         (string_compare(answer, "5") != 0) &&
         (string_compare(answer, "avsluta") != 0)) {
    string_entry("Svara med 1-5 för att välja ett av alternativen eller skriv \"avsluta\" för att avsluta och återvända till huvudmenyn.", answer);
    
    if (string_compare(answer, "avsluta") == 0) {
      bool quit = string_yes_no_question("Är du säker på att du vill avsluta?");
      
      if (quit) {
        printf("Du har valt att avsluta.\n");
        free(answer);
        return false;
      }
    }
  }
  
  switch (string_to_int(answer)) {
    case 1:
      node_name_edit(input_node);
      break;
      
    case 2:
      ware_edit_description(node_get_ware(input_node));
      break;
      
    case 3:
      ware_edit_price(node_get_ware(input_node));
      break;
      
    case 4:
      ware_edit_amount(node_get_ware(input_node));
      break;
      
    case 5:
      io_ware_edit_shelves(input_tree, node_get_ware(input_node));
      break;
      
    default:
      break;
  }
  
  free(answer);
  return true;
}

/* Interface for editing the shelves where the input_ware is located */
void io_ware_edit_shelves(tree *input_tree, ware *input_ware) {
  shelves_show(ware_get_shelves(input_ware), "shelf");
  shelves_list *input_list = ware_get_shelves(input_ware);
  
  int shelves_size = shelves_list_get_size(input_list);
  int choice = 0;
  
  while (!io_ware_edit_choose_shelves(shelves_size, &choice));
  
  list_node *list_node_to_edit = find_list_node_by_index(input_list, choice-1);
  shelf *shelf_to_edit = (shelf *) list_node_get_data(list_node_to_edit);
  io_edit_shelf(input_tree, shelf_to_edit);
  ware_update_amount(input_ware);
}

void io_edit_shelf(tree *input_tree, shelf *input_shelf) {
  shelf_show(input_shelf);
  char *answer = string_new();
  string_entry("\nSvara med 1 eller 2 för att välja ett av alternativen.\n1. Redigera namn\n2. Redigera antal", answer);
  
  while ((!string_equals(answer, "1")) && (!string_equals(answer, "2"))) {
    string_entry("Vänligen svara med 1 eller 2 för att välja ett av alternativen.", answer);
  }
  
  if (string_equals(answer, "1")) {
    bool already_taken = true;
    char *new_shelf_location = string_new();
    while (already_taken) {
      string_entry("Vänligen ange ett nytt hyllnamn:", new_shelf_location);
      already_taken = find_shelf_in_tree(new_shelf_location, input_tree);
      
      if (!already_taken) break;
      else printf("Du angav en redan upptagen hylla.\n");
    }
    free(shelf_get_location(input_shelf));
    shelf_set_location(input_shelf, new_shelf_location);
  }
  
  if (string_equals(answer, "2")) {
    io_shelf_edit_quantity(input_shelf);
    // TODO!!! Ifall en hyllas antal är 0 efter redigering, ska hyllan tas bort
  }
  
  free(answer);  
}

void io_shelf_edit_quantity(shelf *input_shelf) {
  char *answer = string_new();
  string_entry("Svara med 1-3 för att välja ett av alternativen.\n1. Öka antalet av varan på denna hylla\n2. Minska antalet av varan på denna hylla\n3. Ange nytt antal av varan på denna hylla", answer);
  while ((!string_equals(answer, "1")) && 
         (!string_equals(answer, "2")) && 
         (!string_equals(answer, "3"))) {
    string_entry("Vänligen svara med 1-3 för att välja ett av alternativen.", answer);
  }
  
  if (string_equals(answer, "1")) {
    int increment = 0;
    int_entry("Vänligen ange hur mycket du vill öka antalet med:", &increment);
    shelf_increment_quantity(input_shelf, increment);
  }
  if (string_equals(answer, "2")) {
    int decrement = 0;
    int_entry("Vänligen ange hur mycket du vill minska antalet med:", &decrement);
    shelf_decrement_quantity(input_shelf, decrement);
  }
  if (string_equals(answer, "3")) {
    int new_quantity = 0;
    int_entry("Vänligen ange varans nya antal på denna hylla:", &new_quantity);
    shelf_set_quantity(input_shelf, new_quantity);
  }
  
  free(answer);
}

bool io_ware_edit_choose_shelves(int shelves_size, int *choice) {
  int_entry("Vilken hyllplats skall ändras?", choice);  
  bool valid_choice = false;
  valid_choice = (*choice >= 1) && (*choice <= shelves_size);
  
  if (!valid_choice) {
    printf("Vänligen skriv en siffra mellan 1-%d för att välja en av hyllplatserna.\n", shelves_size);
    return false;
  } 
  
  return true;
}

/// Interface for selecting wares from the tree and putting them in a shopping cart
void io_shopping_cart(tree *main_tree, tree *shopping_cart_tree) {
  bool keep_going = true;
  while (keep_going) {
    io_list_shopping_cart(shopping_cart_tree);
    printf("\nVaror i databasen:\n\n");
    tree_list_nodes(main_tree);
    int choice = 0;
    while (!io_choose_ware("Välj vara att packa på pallen", tree_size(main_tree), &choice));
    
    node *chosen_node = find_node_by_index(main_tree, choice);
    if (chosen_node == NULL) {
      printf("io_shopping_cart(): chosen_node = NULL...\n");
      continue;
    }
    node *existing_node = find_node_in_tree(node_get_key(chosen_node), shopping_cart_tree);
    if (existing_node != NULL) {
      char *answer = string_new();
      string_entry("Denna varan finns redan på din pall. Vill du öka antalet?", answer);
      if (string_equals(answer, "ja")) {
        free(answer);
        int increment = 0;
        int_entry("Hur många fler av varan vill du lägga till?", &increment);
        ware *existing_ware = node_get_ware(existing_node);
        ware_increment_amount(existing_ware, increment);
      }
      else if (string_equals(answer, "nej")) free(answer);
      
      continue;
    }
    printf("-----------------------------------\n");
    node_show(chosen_node);
    
    node *shopping_node = node_new();
    node_copy(shopping_node, chosen_node);
    set_left_node(shopping_node, NULL);
    set_parent_node(shopping_node, NULL);
    set_right_node(shopping_node, NULL);
    
    int max_amount = ware_get_amount(node_get_ware(chosen_node));
    int insert_amount = 0;
    while (!io_choose_ware_amount_to_shop(max_amount, &insert_amount));
    ware_set_amount(node_get_ware(shopping_node), insert_amount);
    
    tree_node_add(shopping_cart_tree, shopping_node);
    
    // bool keep_going = string_yes_no_question("Vill du packa en till vara?");
    char *answer = string_new();
    string_entry("Vill du packa en till vara?", answer);
    if (string_equals(answer, "ja")) keep_going = true;
    else if (string_equals(answer, "nej")) keep_going = false;
    free(answer);
  }
  
}

void io_list_shopping_cart(tree *shopping_cart_tree) {
  if (tree_size(shopping_cart_tree) == 0) printf("Din pall är tom.\n");
  else {
    printf("\nDin pall:\n");
    tree_list_nodes(shopping_cart_tree);
    int total_price = io_total_price_of_cart(shopping_cart_tree);
    printf("Totalt pris för pallen: %d kr", total_price);
  }
}

bool io_choose_ware(char *input_text, int tree_size, int *choice) {
  int_entry(input_text, choice);  
  bool valid_choice = false;
  valid_choice = (*choice >= 1) && (*choice <= tree_size);
  
  if (!valid_choice) {
    printf("Vänligen skriv en siffra mellan 1-%d för att välja en av varorna i databasen.\n", tree_size);
    return false;
  } 
  
  return true;
}

bool io_choose_ware_amount_to_shop(int max_amount, int *choice) {
  int_entry("Hur många vill du packa?", choice);  
  bool valid_choice = false;
  valid_choice = (*choice >= 1) && (*choice <= max_amount);
  
  if (*choice > max_amount) {
    printf("Det finns endast %d styck av denna vara, vänligen välj ett antal mellan 1-%d.\n", max_amount, max_amount);
    return false;
  }
  
  if (*choice < 1) {
    printf("Vänligen välj ett antal mellan 1-%d.\n", max_amount);
    return false;
  } 
  
  return true;
}

int io_total_price_of_cart(tree *shopping_cart_tree) {
  int total_price = 0;
  node **tree_root = tree_get_root(shopping_cart_tree);
  
  if (tree_size(shopping_cart_tree) == 1) {
    
    ware *root_ware = node_get_ware(*tree_root);
    for (int i = 0; i < ware_get_amount(root_ware); i++) total_price += ware_get_price(root_ware);
  }
  else {
    io_total_price_of_cart_aux(*tree_root, &total_price);
  }
  
  return total_price;
}

void io_total_price_of_cart_aux(node *iter, int *price_ptr) {
  if (get_left_node(iter)) io_total_price_of_cart_aux(get_left_node(iter), price_ptr);
  ware *iter_ware = node_get_ware(iter);
  for (int i = 0; i < ware_get_amount(iter_ware); i++) *price_ptr += ware_get_price(iter_ware);
  if (get_right_node(iter)) io_total_price_of_cart_aux(get_right_node(iter), price_ptr);
}

#include "SearchBar.h"

int main()
{
	SearchBar sb;
	sb.addToSearchHistory("Hello");
	sb.addToSearchHistory("Hey");
	sb.addToSearchHistory("Heydan");
	sb.autocomplete("He");
	sb.printAutoComplete();
}
  char ch;

  std::cout << "A - Add Score\n"
            << "C - Calculate Average\n"
            << "M - Find the minimum score\n"
            << "X - Find the maximum score\n"
            << "Q - Quit\n";

  while (std::cin >> ch && toupper(ch) != 'Q') {
    while (std::cin.get() != '\n')
      continue;
    if (!isalpha(ch)) {
      std::cout << '\a';
      continue;
    }
  
    switch(ch) {
      case 'A':
      case 'a': std::cout << "Enter Score: ";
                std::cin >> score;
                break;
      case 'P':
      case 'p': if (st.isempty())
                  std::cout << "Stack empty\n";
                else {
                  st.pop(po);
                  std::cout << "PO #" << po << " popped\n";
                }
                break;
    }
    std::cout << "A - Add Order\n"
              << "P - Process Order\n"
              << "Q - Quit\n";
     
  }
  std::cout << "\nDone.\n";

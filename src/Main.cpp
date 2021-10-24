#include <iostream>
#include <cpr/cpr.h>

int main(int argc, char **argv) {
  using namespace cpr;
  using namespace std;

  auto page = Get(Url("https://example.com"), VerifySsl(false));

  cout << page.text;
}
#include <iostream>
#include <cpr/cpr.h>

int main(int argc, char **argv) {
  using namespace cpr;
  using namespace std;

  auto exampleUrl = Url("https://example.com");
  auto sslConfig = VerifySsl(false);
  auto examplePage = Get(exampleUrl, sslConfig);

  cout << examplePage.text;
}
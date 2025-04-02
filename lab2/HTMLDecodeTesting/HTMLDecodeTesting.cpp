#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../HTMLDecode/include/DecodeOperations.h"

TEST_CASE("HtmlDecode Testing", "[HtmlDecode]")
{
    std::string line1 = "Hello & World";
    std::string expected1 = "Hello & World";

    std::string line2 = "Cat &lt;says&gt; &quot;Meow&quot;.";
    std::string expected2 = "Cat <says> \"Meow\".";

    std::string line3 = "";
    std::string expected3 = "";

    std::string line4 = "Test &unknown; and &";
    std::string expected4 = "Test &unknown; and &";

    std::string line5 = "M&amp;M&apos;s";
    std::string expected5 = "M&M's";

    std::string line6 = "&quot;&apos;&lt;&amp;&gt;&apos;&quot;";
    std::string expected6 = "\"\'<&>\'\"";

    CHECK(HtmlDecode(line1) == expected1);
    CHECK(HtmlDecode(line2) == expected2);
    CHECK(HtmlDecode(line3) == expected3);
    CHECK(HtmlDecode(line4) == expected4);
    CHECK(HtmlDecode(line5) == expected5);
    CHECK(HtmlDecode(line6) == expected6);
}
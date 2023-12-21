//#include "gtest/gtest.h"
//#include "../src/core/AstPrinter.hpp"
//#include "../src/core/ConfigInfo.hpp"
//#include "../src/core/Expr.hpp"
//#include "../src/core/common.hpp"

//TEST(AstPrinterTest, VisitMainContextExpr) {
//    AstPrinter printer;
//    ConfigInfo conf;
//    MainContext mainContext(new ServerContext(), new ServerContext());
//    testing::internal::CaptureStdout();
//    printer.visitMainContextExpr(mainContext, conf);
//    std::string output = testing::internal::GetCapturedStdout();
//    EXPECT_EQ(output, "(group)");
//}

//TEST(AstPrinterTest, VisitServerContextExpr) {
//    AstPrinter printer;
//    ConfigInfo conf;
//    ServerContext serverContext(new ServerContext(), new ServerContext());
//    testing::internal::CaptureStdout();
//    printer.visitServerContextExpr(serverContext, conf);
//    std::string output = testing::internal::GetCapturedStdout();
//    EXPECT_EQ(output, "(server)");
//}

//TEST(AstPrinterTest, VisitLocationContextExpr) {
//    AstPrinter printer;
//    ConfigInfo conf;
//    LocationContext locationContext(new LocationContext(), new LocationContext());
//    testing::internal::CaptureStdout();
//    printer.visitLocationContextExpr(locationContext, conf);
//    std::string output = testing::internal::GetCapturedStdout();
//    EXPECT_EQ(output, "(location)");
//}

//TEST(AstPrinterTest, VisitDirectiveExpr) {
//    AstPrinter printer;
//    ConfigInfo conf;
//    Token token(PARAMETER, "directive", 1);
//    Directive directive(token, new Parameter());
//    testing::internal::CaptureStdout();
//    printer.visitDirectiveExpr(directive, conf);
//    std::string output = testing::internal::GetCapturedStdout();
//    EXPECT_EQ(output, "(directive)");
//}

//TEST(AstPrinterTest, VisitParameterExpr) {
//    AstPrinter printer;
//    ConfigInfo conf;
//    std::vector<std::string> params = {"param1", "param2"};
//    Parameter parameter(params);
//    testing::internal::CaptureStdout();
//    printer.visitParameterExpr(parameter, conf);
//    std::string output = testing::internal::GetCapturedStdout();
//    EXPECT_EQ(output, "[ param1 param2 ] ");
//}

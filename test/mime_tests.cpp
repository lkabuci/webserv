#include "../include/webserv.h"
#include <gtest/gtest.h>

namespace {

TEST(MIMETypeTest, DefaultConstructor) {
    MIMEType mime;
    EXPECT_EQ(mime.getMimeTypeForExtension("js"), "application/javascript");
    EXPECT_EQ(mime.getMimeTypeForExtension("css"), "text/css");
    EXPECT_EQ(mime.getMimeTypeForExtension("ico"), "image/x-icon");
    EXPECT_EQ(mime.getMimeTypeForExtension("pdf"), "application/pdf");
    EXPECT_EQ(mime.getMimeTypeForExtension("rpm"),
              "application/x-redhat-package-manager");
    EXPECT_EQ(mime.getMimeTypeForExtension("mp4"), "video/mp4");
}

// TODO: other tests for other mimetype file will be added later
// TEST(MIMETypeTest, GetMimeTypeForExtension) {
//     MIMEType mime("../config/mime.types");
//     EXPECT_EQ(mime.getMimeTypeForExtension("html"), "text/html");
//     EXPECT_EQ(mime.getMimeTypeForExtension("jpg"), "image/jpeg");
// }

} // namespace

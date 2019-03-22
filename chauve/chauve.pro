#-------------------------------------------------
#
# Project created by QtCreator 2019-03-16T20:31:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chauve
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

RESOURCES += \
    application.qrc

SOURCES += \
    google/protobuf/io/coded_stream.cc \
    google/protobuf/io/coded_stream_unittest.cc \
    google/protobuf/io/gzip_stream.cc \
    google/protobuf/io/printer.cc \
    google/protobuf/io/printer_unittest.cc \
    google/protobuf/io/strtod.cc \
    google/protobuf/io/tokenizer.cc \
    google/protobuf/io/tokenizer_unittest.cc \
    google/protobuf/io/zero_copy_stream.cc \
    google/protobuf/io/zero_copy_stream_impl.cc \
    google/protobuf/io/zero_copy_stream_impl_lite.cc \
    google/protobuf/io/zero_copy_stream_unittest.cc \
    google/protobuf/stubs/bytestream.cc \
    google/protobuf/stubs/bytestream_unittest.cc \
    google/protobuf/stubs/common.cc \
    google/protobuf/stubs/common_unittest.cc \
    google/protobuf/stubs/int128.cc \
    google/protobuf/stubs/int128_unittest.cc \
    google/protobuf/stubs/io_win32.cc \
    google/protobuf/stubs/io_win32_unittest.cc \
    google/protobuf/stubs/mathlimits.cc \
    google/protobuf/stubs/status.cc \
    google/protobuf/stubs/status_test.cc \
    google/protobuf/stubs/statusor.cc \
    google/protobuf/stubs/statusor_test.cc \
    google/protobuf/stubs/stringpiece.cc \
    google/protobuf/stubs/stringpiece_unittest.cc \
    google/protobuf/stubs/stringprintf.cc \
    google/protobuf/stubs/stringprintf_unittest.cc \
    google/protobuf/stubs/structurally_valid.cc \
    google/protobuf/stubs/structurally_valid_unittest.cc \
    google/protobuf/stubs/strutil.cc \
    google/protobuf/stubs/strutil_unittest.cc \
    google/protobuf/stubs/substitute.cc \
    google/protobuf/stubs/template_util_unittest.cc \
    google/protobuf/stubs/time.cc \
    google/protobuf/stubs/time_test.cc \
    google/protobuf/testing/file.cc \
    google/protobuf/testing/googletest.cc \
    google/protobuf/testing/zcgunzip.cc \
    google/protobuf/testing/zcgzip.cc \
    google/protobuf/util/internal/datapiece.cc \
    google/protobuf/util/internal/default_value_objectwriter.cc \
    google/protobuf/util/internal/default_value_objectwriter_test.cc \
    google/protobuf/util/internal/error_listener.cc \
    google/protobuf/util/internal/field_mask_utility.cc \
    google/protobuf/util/internal/json_escaping.cc \
    google/protobuf/util/internal/json_objectwriter.cc \
    google/protobuf/util/internal/json_objectwriter_test.cc \
    google/protobuf/util/internal/json_stream_parser.cc \
    google/protobuf/util/internal/json_stream_parser_test.cc \
    google/protobuf/util/internal/object_writer.cc \
    google/protobuf/util/internal/proto_writer.cc \
    google/protobuf/util/internal/protostream_objectsource.cc \
    google/protobuf/util/internal/protostream_objectsource_test.cc \
    google/protobuf/util/internal/protostream_objectwriter.cc \
    google/protobuf/util/internal/protostream_objectwriter_test.cc \
    google/protobuf/util/internal/type_info.cc \
    google/protobuf/util/internal/type_info_test_helper.cc \
    google/protobuf/util/internal/utility.cc \
    google/protobuf/util/delimited_message_util.cc \
    google/protobuf/util/delimited_message_util_test.cc \
    google/protobuf/util/field_comparator.cc \
    google/protobuf/util/field_comparator_test.cc \
    google/protobuf/util/field_mask_util.cc \
    google/protobuf/util/field_mask_util_test.cc \
    google/protobuf/util/json_util.cc \
    google/protobuf/util/json_util_test.cc \
    google/protobuf/util/message_differencer.cc \
    google/protobuf/util/message_differencer_unittest.cc \
    google/protobuf/util/time_util.cc \
    google/protobuf/util/time_util_test.cc \
    google/protobuf/util/type_resolver_util.cc \
    google/protobuf/util/type_resolver_util_test.cc \
    google/protobuf/any.cc \
    google/protobuf/any.pb.cc \
    google/protobuf/any_test.cc \
    google/protobuf/api.pb.cc \
    google/protobuf/arena.cc \
    google/protobuf/arena_test_util.cc \
    google/protobuf/arena_unittest.cc \
    google/protobuf/arenastring_unittest.cc \
    google/protobuf/descriptor.cc \
    google/protobuf/descriptor.pb.cc \
    google/protobuf/descriptor_database.cc \
    google/protobuf/descriptor_database_unittest.cc \
    google/protobuf/descriptor_unittest.cc \
    google/protobuf/drop_unknown_fields_test.cc \
    google/protobuf/duration.pb.cc \
    google/protobuf/dynamic_message.cc \
    google/protobuf/dynamic_message_unittest.cc \
    google/protobuf/empty.pb.cc \
    google/protobuf/extension_set.cc \
    google/protobuf/extension_set_heavy.cc \
    google/protobuf/extension_set_unittest.cc \
    google/protobuf/field_mask.pb.cc \
    google/protobuf/generated_message_reflection.cc \
    google/protobuf/generated_message_reflection_unittest.cc \
    google/protobuf/generated_message_table_driven.cc \
    google/protobuf/generated_message_table_driven_lite.cc \
    google/protobuf/generated_message_util.cc \
    google/protobuf/implicit_weak_message.cc \
    google/protobuf/lite_arena_unittest.cc \
    google/protobuf/lite_unittest.cc \
    google/protobuf/map_field.cc \
    google/protobuf/map_field_test.cc \
    google/protobuf/map_lite_test_util.cc \
    google/protobuf/map_test.cc \
    google/protobuf/map_test_util.cc \
    google/protobuf/message.cc \
    google/protobuf/message_lite.cc \
    google/protobuf/message_unittest.cc \
    google/protobuf/no_field_presence_test.cc \
    google/protobuf/parse_context.cc \
    google/protobuf/preserve_unknown_enum_test.cc \
    google/protobuf/proto3_arena_lite_unittest.cc \
    google/protobuf/proto3_arena_unittest.cc \
    google/protobuf/proto3_lite_unittest.cc \
    google/protobuf/reflection_ops.cc \
    google/protobuf/reflection_ops_unittest.cc \
    google/protobuf/repeated_field.cc \
    google/protobuf/repeated_field_reflection_unittest.cc \
    google/protobuf/repeated_field_unittest.cc \
    google/protobuf/service.cc \
    google/protobuf/source_context.pb.cc \
    google/protobuf/struct.pb.cc \
    google/protobuf/test_util.cc \
    google/protobuf/test_util_lite.cc \
    google/protobuf/text_format.cc \
    google/protobuf/text_format_unittest.cc \
    google/protobuf/timestamp.pb.cc \
    google/protobuf/type.pb.cc \
    google/protobuf/unknown_field_set.cc \
    google/protobuf/unknown_field_set_unittest.cc \
    google/protobuf/well_known_types_unittest.cc \
    google/protobuf/wire_format.cc \
    google/protobuf/wire_format_lite.cc \
    google/protobuf/wire_format_unittest.cc \
    google/protobuf/wrappers.pb.cc \
    protobuf/demo.pb.cc \
    protobuf/dota_commonmessages.pb.cc \
    protobuf/dota_shared_enums.pb.cc \
    protobuf/dota_usermessages.pb.cc \
    protobuf/netmessages.pb.cc \
    protobuf/network_connection.pb.cc \
    protobuf/networkbasetypes.pb.cc \
    protobuf/usermessages.pb.cc \
    main.cpp \
    mainwindow.cpp \
    replay.cpp \
    replaymanager.cpp \
    replaywidget.cpp \
    settingsdialog.cpp \
    settingsmanager.cpp

HEADERS += \
    google/protobuf/io/coded_stream.h \
    google/protobuf/io/coded_stream_inl.h \
    google/protobuf/io/gzip_stream.h \
    google/protobuf/io/package_info.h \
    google/protobuf/io/printer.h \
    google/protobuf/io/strtod.h \
    google/protobuf/io/tokenizer.h \
    google/protobuf/io/zero_copy_stream.h \
    google/protobuf/io/zero_copy_stream_impl.h \
    google/protobuf/io/zero_copy_stream_impl_lite.h \
    google/protobuf/stubs/bytestream.h \
    google/protobuf/stubs/callback.h \
    google/protobuf/stubs/casts.h \
    google/protobuf/stubs/common.h \
    google/protobuf/stubs/fastmem.h \
    google/protobuf/stubs/hash.h \
    google/protobuf/stubs/int128.h \
    google/protobuf/stubs/io_win32.h \
    google/protobuf/stubs/logging.h \
    google/protobuf/stubs/macros.h \
    google/protobuf/stubs/map_util.h \
    google/protobuf/stubs/mathlimits.h \
    google/protobuf/stubs/mathutil.h \
    google/protobuf/stubs/mutex.h \
    google/protobuf/stubs/once.h \
    google/protobuf/stubs/platform_macros.h \
    google/protobuf/stubs/port.h \
    google/protobuf/stubs/status.h \
    google/protobuf/stubs/status_macros.h \
    google/protobuf/stubs/statusor.h \
    google/protobuf/stubs/stl_util.h \
    google/protobuf/stubs/stringpiece.h \
    google/protobuf/stubs/stringprintf.h \
    google/protobuf/stubs/strutil.h \
    google/protobuf/stubs/substitute.h \
    google/protobuf/stubs/template_util.h \
    google/protobuf/stubs/time.h \
    google/protobuf/testing/file.h \
    google/protobuf/testing/googletest.h \
    google/protobuf/util/internal/constants.h \
    google/protobuf/util/internal/datapiece.h \
    google/protobuf/util/internal/default_value_objectwriter.h \
    google/protobuf/util/internal/error_listener.h \
    google/protobuf/util/internal/expecting_objectwriter.h \
    google/protobuf/util/internal/field_mask_utility.h \
    google/protobuf/util/internal/json_escaping.h \
    google/protobuf/util/internal/json_objectwriter.h \
    google/protobuf/util/internal/json_stream_parser.h \
    google/protobuf/util/internal/location_tracker.h \
    google/protobuf/util/internal/mock_error_listener.h \
    google/protobuf/util/internal/object_location_tracker.h \
    google/protobuf/util/internal/object_source.h \
    google/protobuf/util/internal/object_writer.h \
    google/protobuf/util/internal/proto_writer.h \
    google/protobuf/util/internal/protostream_objectsource.h \
    google/protobuf/util/internal/protostream_objectwriter.h \
    google/protobuf/util/internal/structured_objectwriter.h \
    google/protobuf/util/internal/type_info.h \
    google/protobuf/util/internal/type_info_test_helper.h \
    google/protobuf/util/internal/utility.h \
    google/protobuf/util/delimited_message_util.h \
    google/protobuf/util/field_comparator.h \
    google/protobuf/util/field_mask_util.h \
    google/protobuf/util/json_util.h \
    google/protobuf/util/message_differencer.h \
    google/protobuf/util/package_info.h \
    google/protobuf/util/time_util.h \
    google/protobuf/util/type_resolver.h \
    google/protobuf/util/type_resolver_util.h \
    google/protobuf/any.h \
    google/protobuf/any.pb.h \
    google/protobuf/api.pb.h \
    google/protobuf/arena.h \
    google/protobuf/arena_impl.h \
    google/protobuf/arena_test_util.h \
    google/protobuf/arenastring.h \
    google/protobuf/descriptor.h \
    google/protobuf/descriptor.pb.h \
    google/protobuf/descriptor_database.h \
    google/protobuf/duration.pb.h \
    google/protobuf/dynamic_message.h \
    google/protobuf/empty.pb.h \
    google/protobuf/extension_set.h \
    google/protobuf/extension_set_inl.h \
    google/protobuf/field_mask.pb.h \
    google/protobuf/generated_enum_reflection.h \
    google/protobuf/generated_enum_util.h \
    google/protobuf/generated_message_reflection.h \
    google/protobuf/generated_message_table_driven.h \
    google/protobuf/generated_message_table_driven_lite.h \
    google/protobuf/generated_message_util.h \
    google/protobuf/has_bits.h \
    google/protobuf/implicit_weak_message.h \
    google/protobuf/inlined_string_field.h \
    google/protobuf/map.h \
    google/protobuf/map_entry.h \
    google/protobuf/map_entry_lite.h \
    google/protobuf/map_field.h \
    google/protobuf/map_field_inl.h \
    google/protobuf/map_field_lite.h \
    google/protobuf/map_lite_test_util.h \
    google/protobuf/map_test_util.h \
    google/protobuf/map_test_util_impl.h \
    google/protobuf/map_type_handler.h \
    google/protobuf/message.h \
    google/protobuf/message_lite.h \
    google/protobuf/metadata.h \
    google/protobuf/metadata_lite.h \
    google/protobuf/package_info.h \
    google/protobuf/parse_context.h \
    google/protobuf/port.h \
    google/protobuf/reflection.h \
    google/protobuf/reflection_internal.h \
    google/protobuf/reflection_ops.h \
    google/protobuf/repeated_field.h \
    google/protobuf/service.h \
    google/protobuf/source_context.pb.h \
    google/protobuf/struct.pb.h \
    google/protobuf/test_util.h \
    google/protobuf/test_util2.h \
    google/protobuf/test_util_lite.h \
    google/protobuf/text_format.h \
    google/protobuf/timestamp.pb.h \
    google/protobuf/type.pb.h \
    google/protobuf/unknown_field_set.h \
    google/protobuf/wire_format.h \
    google/protobuf/wire_format_lite.h \
    google/protobuf/wire_format_lite_inl.h \
    google/protobuf/wrappers.pb.h \
    protobuf/demo.pb.h \
    protobuf/dota_commonmessages.pb.h \
    protobuf/dota_shared_enums.pb.h \
    protobuf/dota_usermessages.pb.h \
    protobuf/netmessages.pb.h \
    protobuf/network_connection.pb.h \
    protobuf/networkbasetypes.pb.h \
    protobuf/usermessages.pb.h \
    mainwindow.h \
    replay.h \
    replaymanager.h \
    replaywidget.h \
    settingsdialog.h \
    settingsmanager.h

FORMS += \
    mainwindow.ui \
    replaywidget.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    protobuf/demo.proto \
    protobuf/dota_commonmessages.proto \
    protobuf/dota_shared_enums.proto \
    protobuf/dota_usermessages.proto \
    protobuf/netmessages.proto \
    protobuf/network_connection.proto \
    protobuf/networkbasetypes.proto \
    protobuf/usermessages.proto \
    protobuf/demo.proto \
    protobuf/dota_commonmessages.proto \
    protobuf/dota_shared_enums.proto \
    protobuf/dota_usermessages.proto \
    protobuf/netmessages.proto \
    protobuf/network_connection.proto \
    protobuf/networkbasetypes.proto \
    protobuf/usermessages.proto

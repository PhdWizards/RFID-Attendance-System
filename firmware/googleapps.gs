function doGet(e) {
  var ss = SpreadsheetApp.getActiveSpreadsheet();

  var attendance = ss.getSheetByName("Attendance");
  var users = ss.getSheetByName("Users");
  var state = ss.getSheetByName("State");

  var uid = e.parameter.uid;

  // ===== Получаем имя =====
  var usersData = users.getDataRange().getValues();
  var name = "Unknown";

  for (var i = 1; i < usersData.length; i++) {
    if (usersData[i][0] == uid) {
      name = usersData[i][1];
      break;
    }
  }

  // ===== Получаем состояние =====
  var stateData = state.getDataRange().getValues();
  var lastStatus = "OUT";
  var rowIndex = -1;

  for (var i = 1; i < stateData.length; i++) {
    if (stateData[i][0] == uid) {
      lastStatus = stateData[i][1];
      rowIndex = i + 1;
      break;
    }
  }

  var newStatus = (lastStatus == "IN") ? "OUT" : "IN";

  // ===== Обновляем состояние =====
  if (rowIndex == -1) {
    state.appendRow([uid, newStatus]);
  } else {
    state.getRange(rowIndex, 2).setValue(newStatus);
  }

  // ===== Записываем посещение =====
  attendance.appendRow([
    name,
    uid,
    new Date(),
    newStatus
  ]);

  // ===== Возвращаем статус =====
  return ContentService.createTextOutput(newStatus);
}

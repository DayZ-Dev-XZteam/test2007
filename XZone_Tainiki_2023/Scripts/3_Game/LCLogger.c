class LCLogger {
	
	void LCLogger() {
		//pll
	}

	static void Log(string txt) {
		string file_path = "$profile:\\XZone_Tainiki\\XZone_Tainiki.log";
		FileHandle logFile = OpenFile(file_path, FileMode.APPEND);
		if (logFile != 0) {
				FPrintln(logFile, GetDate() + " [XZone_Tainiki] " + txt);
				CloseFile(logFile);
		}
	}
	
	static private string GetDate(bool fileFriendly = false) {
		int year, month, day, hour, minute, second;

		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);


		string date = day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2);
		if (fileFriendly) {
			date.Replace(" ", "_");
			date.Replace(".", "-");
			date.Replace(":", "-");
		}

		return date;
	}
}
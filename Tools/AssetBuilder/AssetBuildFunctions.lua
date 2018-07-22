
-- Environment Variables
local EngineSourceContentDir, GameInstallDir, ExternalDir, QtBinDir

do
	-- EngineSourceContentDir
	do
		local errorMessage
		EngineSourceContentDir, errorMessage = GetEnvironmentVariable( "EngineSourceContentDir" )
		if not EngineSourceContentDir then
			error( errorMessage )
		end
	end

	-- GameInstallDir
	do 
		local errorMessage
		GameInstallDir, errorMessage = GetEnvironmentVariable("GameInstallDir")

		if not GameInstallDir then 
			error(errorMessage)
		else
			CreateDirectoryIfItDoesntExist( GameInstallDir )
		end
	end

	-- External Dir
	do 
		local errorMessage
		ExternalDir, errorMessage = GetEnvironmentVariable("ExternalDir")
		if not ExternalDir then 
			error(errorMessage)
		end
	end
		

	-- Copy Qt .dll file
	do 
		local errorMessage
		QtBinDir, errorMessage = GetEnvironmentVariable("QtBinDir")

		if not QtBinDir then 
			error(errorMessage)
		else
			local Files = GetFilesInDirectory( QtBinDir )

			for i, File in ipairs( Files ) do
				local sourceFileName = File:sub( #QtBinDir + 1 )

				local targetPath = GameInstallDir .. sourceFileName
				
				print( File ) 
				print( targetPath )

				local result, errorMessage = CopyFile(File, targetPath)

				if result then
					print( "Copied " .. sourceFileName )
				else
					OutputMessage( "The file couldn't be copied to \"" .. targetPath .. "\": " .. errorMessage )
				end
			end
		end
	end


end
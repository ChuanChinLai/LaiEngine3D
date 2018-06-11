
-- Environment Variables
local EngineSourceContentDir, GameInstallDir, ExternalDir, SDLBinDir

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
		
end
savedcmd_/home/vm-sus/new_folder/linux_driver/exercise_kernel.mod := printf '%s\n'   exercise_kernel.o | awk '!x[$$0]++ { print("/home/vm-sus/new_folder/linux_driver/"$$0) }' > /home/vm-sus/new_folder/linux_driver/exercise_kernel.mod

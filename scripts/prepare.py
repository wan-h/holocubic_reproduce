import os
import shutil

# ROOT_PATH = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ROOT_PATH = "."

def setup_tft():
    print("*" * 20 + " setup tft " + "*" * 20)
    tft_config_local = os.path.join(ROOT_PATH, "include", "User_Setup_Select.h")
    if not os.path.exists(tft_config_local):
        print(f"please check tft file in {tft_config_local}")
        return
    libdeps = os.path.join(ROOT_PATH, ".pio", "libdeps", "")
    for env in os.listdir(libdeps):
        tft_lib_path = os.path.join(libdeps, env, "TFT_eSPI")
        # copy文件
        try:
            shutil.copy2(tft_config_local, tft_lib_path)
            print(f"tft config copy: {tft_config_local} ---> {tft_lib_path}")
        except Exception as e:
            print(f"Fail to copy: {tft_config_local} ---> {tft_lib_path}, {e}")


setup_tft()
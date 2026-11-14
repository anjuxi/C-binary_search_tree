import subprocess;
import tempfile;
from pathlib import Path;


def compile_and_run(project_dir, temp_dir, executable_name, source_paths):
    executable_path = Path(temp_dir) / executable_name;
    compile_command = [
        "gcc",
        "-std=c11",
        "-Wall",
        "-Wextra",
        "-Wpedantic",
        "-Werror",
    ];
    compile_command.extend(str(source_path) for source_path in source_paths);
    compile_command.extend(["-o", str(executable_path)]);

    # 编译和运行分开执行，便于定位失败步骤。
    subprocess.run(compile_command, cwd=project_dir, check=True);
    subprocess.run([str(executable_path)], cwd=project_dir, check=True);


def main():
    project_dir = Path(__file__).resolve().parent;
    library_source = project_dir / "tree.c";
    test_source = project_dir / "test_tree.c";
    demo_source = project_dir / "demo.c";

    with tempfile.TemporaryDirectory(prefix="c_binary_search_tree_") as temp_dir:
        compile_and_run(project_dir, temp_dir, "tree_test.exe", [library_source, test_source]);
        compile_and_run(project_dir, temp_dir, "tree_demo.exe", [library_source, demo_source]);

    print("测试和演示均通过！");


if __name__ == "__main__":
    main();

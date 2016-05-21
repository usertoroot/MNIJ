using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using KIN;
using CommandLine;
using CommandLine.Text;
using System.IO;

namespace MNIJ
{
    class Program
    {
        private sealed class Arguments
        {
            [Option("e", "executable", Required = false, HelpText = "The name of the executable to inject into.")]
            public string ExecutableName = "Dawpdoj.exe";

            [Option("d", "dllname", Required = false, HelpText = "The name of the dll to inject.")]
            public string DllName = "Spoof.dll";

            [Option("f", "function", Required = false, HelpText = "The name of the initialization function.")]
            public string FunctionName = "Initialize";

            [HelpOption(HelpText = "Display this help screen.")]
            public string GetUsage()
            {
                var help = new HelpText("KIN based injector.", "KDA ofc! v1.0");
                help.AdditionalNewLineAfterOption = true;
                help.AddOptions(this);
                return help;
            }
        }

        private static void Main(string[] args)
        {
            Arguments a = new Arguments();
            var parser = new CommandLineParser(new CommandLineParserSettings(Console.Error));
            if (!parser.ParseArguments(args, a))
                return;

            Console.WriteLine("Injecting '{0}' into '{1}' calling '{2}'.", a.ExecutableName, a.DllName, a.FunctionName);
            Console.WriteLine(a.DllName);
            Console.WriteLine(a.FunctionName);

            using (KProcess process = new KProcess())
            {
                process.Open(Path.GetFileNameWithoutExtension(a.ExecutableName));
                process.LoadLibrary(Environment.CurrentDirectory + "\\" + a.DllName, a.FunctionName);
            }

            Console.WriteLine("Success!");
        }
    }
}

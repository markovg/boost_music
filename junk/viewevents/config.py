


def do_config():
    import yaml
    import getopt, sys

    usage = """

    uasge: viewevents -c config.yaml neuronGrid.yaml

    """

    class Conf(object):
        pass

    try:
        opts, args = getopt.getopt(sys.argv[1:], "c:")

    except getopt.GetoptError, err:
        # print help information and exit:
        print str(err) # will print something like "option -a not recognized"
        print usage
        sys.exit(2)

    conf_file = None
    for o, a in opts:
        if o == "-c":
            conf_file = a
        else:
            assert False, "should not get here"

    if not len(args)==1 or not conf_file:
        print usage
        sys.exit(2)

    conf_data = yaml.load(file(conf_file))

    c = Conf()
    c.__dict__.update(conf_data)
    

